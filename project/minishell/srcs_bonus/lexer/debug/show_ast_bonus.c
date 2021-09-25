/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:41:20 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/30 19:41:21 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static void	show_connect(t_ast *todo, void (*f)(t_ast *el))
{
	t_connection	*elem;

	elem = todo->item;
	if (todo->type == OR)
	{
		printf("OR list\n");
		f(elem->left);
		printf("OR false\n");
		f(elem->right);
	}
	else if (todo->type == AND)
	{
		printf("AND list\n");
		f(elem->left);
		printf("AND true\n");
		f(elem->right);
	}
}

static void	show_pipelines(t_ast *todo, void (*f)(t_ast *el))
{
	t_pipeline	*elem;
	t_list		*curr;
	t_ast		*cmd;

	elem = todo->item;
	curr = elem->pipe_sequence;
	printf("Pipelines\n");
	while (curr)
	{
		cmd = curr->content;
		f(cmd);
		curr = curr->next;
	}
}

static void	show_cmd(t_ast *todo, void (*f)(t_ast *el))
{
	t_tokens	*elem;

	(void)f;
	elem = todo->item;
	printf("Simple cmd :");
	while (elem)
	{
		printf(" [%s]", elem->word);
		elem = elem->next;
	}
	printf("\n");
}

static void	show_sub(t_ast *todo, void (*f)(t_ast *el))
{
	t_ast	*cmd;

	cmd = todo->item;
	printf("Compound list\n");
	f(cmd);
	printf("Quit Compound list\n");
}

void	show_ast(t_ast *todo)
{
	if (todo->type == SUB)
		show_sub(todo, show_ast);
	else if (todo->type == PIPE)
		show_pipelines(todo, show_ast);
	else if (todo->type == OR || todo->type == AND)
		show_connect(todo, show_ast);
	else
		show_cmd(todo, show_ast);
}
