/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 19:00:37 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/06 19:00:38 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	one(t_tokens **list, char **cmd, int *index)
{
	char		buffer[4096];
	t_tokens	*curr;

	curr = (*list);
	ft_memset(buffer, 0, 4096);
	while (curr && curr->type != BLANK && ft_strcmp(curr->word, "*"))
	{
		ft_strcat(buffer, curr->word);
		curr = curr->next;
	}
	cmd[*index] = ft_strdup(buffer);
	manage_heap(CREATE_CMD, cmd[*index]);
	(*list) = curr;
	++*index;
}

static void	reader(char *name, char **cmd, int *size)
{
	DIR				*dir;
	struct dirent	*files;

	dir = opendir(name);
	while (1)
	{
		files = readdir(dir);
		if (files)
		{
			if (files->d_name[0] != '.')
			{
				if (cmd)
				{
					cmd[*size] = strdup(files->d_name);
					manage_heap(CREATE_CMD, cmd[*size]);
				}
				++*size;
			}
		}
		else
			break ;
	}
	closedir(dir);
}

static char	**new_cmd(t_tokens *list)
{
	char	**cmd;
	int		size;

	size = 1;
	while (list)
	{
		if (list->type == BLANK)
			++size;
		else if (!ft_strcmp(list->word, "*"))
			reader(".", NULL, &size);
		list = list->next;
	}
	cmd = ft_calloc(size + 1, sizeof(char *));
	manage_heap(CREATE_CMD, cmd);
	return (cmd);
}

char	**cmd_words(t_tokens *list, t_var *vars, int flag)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = NULL;
	if (list)
	{
		if (flag)
			expand(&list, vars, flag);
		cmd = new_cmd(list);
		while (list)
		{
			if (!ft_strcmp(list->word, "*"))
				reader(".", cmd, &i);
			else
				one(&list, cmd, &i);
			if (list)
				list = list->next;
		}
	}
	return (cmd);
}