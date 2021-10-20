/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 01:58:53 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/02 01:59:30 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static void	simple_(char *type, char *file, int *stream, int *err)
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

static void	read_(char *file, char *delim, int *fd)
{
	char		*new;
	struct stat	s;
	int			i;

	g_err = HERE;
	i = dup(STDIN_FILENO);
	*fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0660);
	while (42)
	{
		new = readline("heredoc>");
		manage_heap(HERE, new);
		if (fstat(STDIN_FILENO, &s) < 0 && !close(*fd) && !unlink(file)
			&& !dup2(i, STDIN_FILENO))
			return ;
		else if (!new || !ft_strcmp(new, delim))
			break ;
		write(*fd, new, ft_strlen(new));
		write(*fd, "\n", 1);
	}
	if (!new)
		write(2, "\nwarning: here-document delimited by end-of-file\n", 49);
	close(*fd);
	*fd = open(file, O_CLOEXEC | O_RDONLY);
	unlink(file);
	g_err = 0;
}

void	heredoc_(t_cmd *cmd)
{
	static char	file[9] = "/tmp/`aa\0";
	t_tokens	*redir;
	int			i;

	redir = (t_tokens *)cmd->redir;
	while (redir)
	{
		if (!ft_strcmp(redir->word, "<<"))
		{
			i = -1;
			while (++i < 3)
			{
				if (ft_isalpha(file[i + 5] + 1))
				{
					++file[i + 5];
					break ;
				}
			}
			redir = redir->next;
			read_(file, redir->word, &cmd->heredoc);
		}
		redir = redir->next;
	}
}

static void	apply_(char **redir, t_var *vars, int *stream, int *err)
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
			expand(&curr, vars, WORD);
			if ((curr->next || !curr->word) && ++*err)
			{
				write(2, file, ft_strlen(file));
				write(2, ": ambigous redirect\n", 20);
			}
			else
				simple_(redir[i], curr->word, stream, err);
		}
	}
}

char	make_redir(t_cmd *cmd, t_var *vars, int *new, int *old)
{
	char	**red;
	int		err;

	err = 0;
	if (cmd->heredoc > 0 )
		old[0] = cmd->heredoc;
	new[0] = old[0];
	new[1] = old[1];
	red = cmd_words(cmd->redir, vars, REDIR);
	if (red)
		apply_(red, vars, new, &err);
	return (err + '0');
}
