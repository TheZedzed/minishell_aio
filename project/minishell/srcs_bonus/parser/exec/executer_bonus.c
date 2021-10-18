/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:59:30 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/30 18:59:32 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static void	exec_or(void *todo, t_var **vars, int *stream)
{
	t_connection	*elem;
	char			*res;

	elem = todo;
	executer(elem->left, vars, stream);
	res = search_var(*vars, "?")->value;
	if (ft_atoi(res) != 0)
	{
		stream[0] = STDIN_FILENO;
		executer(elem->right, vars, stream);
	}
}

static void	exec_and(void *todo, t_var **vars, int *stream)
{
	t_connection	*elem;
	char			*res;

	elem = todo;
	executer(elem->left, vars, stream);
	res = search_var(*vars, "?")->value;
	if (ft_atoi(res) == 0)
	{
		stream[0] = STDIN_FILENO;
		executer(elem->right, vars, stream);
	}
}

static void	exec_sub(void *todo, t_var **vars, int *stream)
{
	t_ast	*elem;
	char	*res;

	elem = todo;
	executer(elem, vars, stream);
	res = search_var(*vars, "?")->value;
	exit(ft_atoi(res));
}

static void	exec_pipe(void *todo, t_var **vars, int *stream)
{
	t_pipeline	*elem;
	int			status;
	char		*res;

	res = NULL;
	elem = todo;
	pipex(elem->pipe_sequence, vars, ft_lstsize(elem->pipe_sequence), stream);
	if (stream[2] != -1)
	{
		waitpid(stream[2], &status, 0);
		if (WIFEXITED(status))
			res = ft_itoa(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			printf("\b\b  \b\b");
			if (WTERMSIG(status) == SIGQUIT)
				printf("\\^Quit (core dumped)\n");
			res = ft_itoa(128 + WTERMSIG(status));
		}
		stream[2] = -1;
		update_var(vars, "?", res, LOCAL);
		manage_heap(CREATE_VAR, res);
	}
	while (wait(&status) > 0)
		;
}

void	executer(t_ast *todo, t_var **vars, int *stream)
{
	static t_exec	*f[5] = {exec_or, exec_sub, exec_cmd, exec_and, exec_pipe};

	if (!g_err)
		f[todo->type](todo->item, vars, stream);
}
