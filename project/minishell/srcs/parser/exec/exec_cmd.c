/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 23:11:47 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/01 23:11:50 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	not_found(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, "\'", 1);
	write(2, str, len);
	write(2, "\': command not found\n", 21);
	exit(127);
}

static char	*stat_cmd(char *src, char *path)
{
	char	buffer[4096];
	t_stat	info;
	char	*res;

	ft_memset(buffer, 0, 4096);
	ft_strcat(buffer, path);
	if (path[ft_strlen(path) - 1] != '/')
		ft_strcat(buffer, "/");
	ft_strcat(buffer, src);
	if (!stat(buffer, &info) && (info.st_mode & S_IFMT) == S_IFREG)
	{
		res = ft_strdup(buffer);
		manage_heap(CREATE_CMD, res);
		return (res);
	}
	return (src);
}

static void	search_path(char **cmd, char *path)
{
	char	**paths;
	char	*res;
	int		i;

	paths = ft_split(path, ':');
	if (paths)
	{
		i = 0;
		manage_heap(CREATE_CMD, paths);
		while (paths[++i])
			manage_heap(CREATE_CMD, paths[i]);
		i = 0;
		while (paths[i])
		{
			res = stat_cmd(cmd[0], paths[i]);
			if (res != cmd[0])
			{
				cmd[0] = res;
				break ;
			}
			++i;
		}
	}
}

void	exec_cmd(void *todo, t_var **vars, int *stream)
{
	t_cmd	*elem;
	int		new[2];
	char	**cmd;
	char	err;

	elem = todo;
	cmd = elem->words;
	err = make_redir(elem, *vars, new, stream);
	if (err == '0' && cmd)
	{
		if (!builtin_(cmd, vars, &err))
		{
			dup2(new[0], STDIN_FILENO);
			dup2(new[1], STDOUT_FILENO);
			if (!ft_strchr(cmd[0], 0x2f) && search_var(*vars, "PATH"))
				search_path(cmd, search_var(*vars, "PATH")->value);
			if (!ft_strchr(cmd[0], 0x2f))
				not_found(cmd[0]);
			else if (execve(cmd[0], cmd, update_env(*vars, 0)))
				not_found(cmd[0]);
		}
	}
	manage_heap(END, NULL);
	exit(err - '0');
}
