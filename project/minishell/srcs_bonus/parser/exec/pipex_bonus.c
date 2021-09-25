/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:59:53 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/29 21:17:08 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static int	should_stop(t_list *cmds, int *pipefd, int *stream)
{
	if (!cmds)
	{
		if (stream[0] != STDIN_FILENO)
			close(stream[0]);
		return (1);
	}
	if (cmds->next)
	{
		pipe(pipefd);
		stream[1] = pipefd[1];
	}
	return (0);
}

static void	should_cont(t_list *cmds, int *pipefd, int *stream)
{
	if (cmds->next)
	{
		if (stream[0] != STDIN_FILENO)
			close(stream[0]);
		close(pipefd[1]);
		stream[0] = pipefd[0];
	}
}

static int	is_blt(char **cmd)
{
	static char	*t[] = {"echo", "pwd", "unset", "env", "exit", "export", "cd",
						NULL};
	int			i;

	i = 0;
	while (t[i] && ft_strcmp(cmd[0], t[i]))
		++i;
	if (t[i])
		return (1);
	return (0);
}

static int	should_skip(t_ast *elem, int size, t_var **vars, int *stream)
{
	static char	err[2] = {0};
	t_cmd		*cmd;
	int			new[2];

	if (elem->type == CMD)
	{
		cmd = elem->item;
		cmd->words = cmd_words(cmd->words, *vars, 1);
		cmd->assign = cmd_words(cmd->assign, *vars, 2);
		if (size == 1)
		{
			if (!cmd->words || (cmd->words && is_blt(cmd->words)))
			{
				*err = make_redir(cmd->redir, *vars, new, stream) + '0';
				if (!cmd->words && cmd->assign)
					assign_(cmd->assign, vars, LOCAL);
				else if (cmd->words && *err == '0')
					builtin_(cmd->words, vars, new, err);
				update_var(vars, "?", err, LOCAL);
				return (1);
			}
		}
	}
	return (0);
}

void	pipex(t_list *cmds, t_var **vars, int size, int *stream)
{
	int	pipefd[2];
	int	pid;

	if (should_stop(cmds, pipefd, stream))
		return ;
	if (!should_skip(cmds->content, size, vars, stream))
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmds->next)
				close(pipefd[0]);
			signal(SIGQUIT, handler);
			dup2(stream[0], STDIN_FILENO);
			dup2(stream[1], STDOUT_FILENO);
			executer(cmds->content, vars, stream);
		}
		else if (pid < 0)
			perror("fork");
		if (!cmds->next)
			stream[2] = pid;
	}
	should_cont(cmds, pipefd, stream);
	return (pipex(cmds->next, vars, size, stream));
}
