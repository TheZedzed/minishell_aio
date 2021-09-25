/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 01:58:53 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/02 01:59:30 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	heredoc(char *file, char *delim, int *stream)
{
	int		fd;
	int		res;
	char	*line;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0660);
	while (42)
	{
		res = get_next_line(STDIN_FILENO, &line);
		if (!res || !ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open(file, O_CLOEXEC | O_RDONLY);
	unlink(file);
	stream[0] = fd;
}

static void	apply_(char *type, char *file, int *stream, int *err)
{
	int	std;
	int	fd;

	std = 0;
	if (!ft_strncmp(type, ">>", 2) && ++std)
		fd = open(file, O_RDWR | O_CLOEXEC | O_APPEND | O_CREAT, 0660);
	else if (!ft_strncmp(type, ">", 1) && ++std)
		fd = open(file, O_RDWR | O_CLOEXEC | O_TRUNC | O_CREAT, 0660);
	else
		fd = open(file, O_RDONLY | O_CLOEXEC);
	if (fd < 0 && ++*err)
		perror(file);
	else
		stream[std] = fd;
}

static void	apply_redir(char **redir, t_var *vars, int *stream, int *err)
{
	t_tokens	*curr;
	char		*file;
	int			i;

	i = -1;
	curr = ft_calloc(1, sizeof(t_tokens));
	manage_heap(CREATE_CMD, curr);
	while (!*err && redir[++i])
	{
		if (ft_strncmp(redir[i], "<<", 2))
		{
			file = redir[i];
			while (*file == '<' || *file == '>')
				++file;
			curr->word = file;
			expand(&curr, vars, 1);
			if ((curr->next || !curr->word) && ++*err)
			{
				write(2, file, ft_strlen(file));
				write(2, ": ambigous redirect\n", 20);
			}
			else
				apply_(redir[i], curr->word, stream, err);
		}
	}
}

int	make_redir(t_tokens *list, t_var *vars, int *new, int *old)
{
	char	**red;
	int		err;
	int		i;

	err = 0;
	new[0] = old[0];
	new[1] = old[1];
	red = cmd_words(list, vars, 0);
	if (red)
	{
		i = 0;
		while (!err && red[i])
		{
			if (!ft_strncmp(red[i], "<<", 2))
				heredoc("/tmp/thezedzed", &red[i][2], new);
			++i;
		}
		apply_redir(red, vars, new, &err);
	}
	return (err);
}
