/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:43:57 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/19 22:50:07 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static t_ast	*compound_cmd(t_tokens **token)
{
	t_tokens	*new;
	t_tokens	*last;
	t_tokens	*curr;

	new = (*token)->next;
	curr = new;
	last = last_token((*token));
	(*token) = last->next;
	while (curr->next != last)
		curr = curr->next;
	curr->next = NULL;
	return (tree(SUB, parser(&new)));
}

static t_ast	*simple_cmd(t_tokens **tokens)
{
	t_tokens	*seq;
	t_tokens	*curr;
	t_cmd		*cmd;

	seq = (*tokens);
	curr = seq;
	cmd = NULL;
	while (curr->next && curr->next->type != CTRL1)
		curr = curr->next;
	(*tokens) = curr->next;
	curr->next = NULL;
	parse_cmd(seq, &cmd);
	return (tree(CMD, cmd));
}

static t_ast	*pipelines(t_tokens **token)
{
	t_list	*seq;
	t_list	*new;
	t_ast	*cmd;

	seq = NULL;
	while (!g_err && *token)
	{
		if ((*token)->type != BLANK && ft_strcmp((*token)->word, "|"))
		{
			if ((*token)->type == CTRL2)
				cmd = compound_cmd(token);
			else
				cmd = simple_cmd(token);
			new = ft_lstnew(cmd);
			manage_heap(PIPELINE, new);
			if (new)
				ft_lstadd_back(&seq, new);
		}
		else
			(*token) = (*token)->next;
	}
	if (g_err)
		return (NULL);
	return (tree(PIPE, pipe_seq(seq)));
}

t_ast	*and_or(t_tokens **cmds, int index)
{
	t_ast	*left;
	t_ast	*right;
	char	*type;

	right = pipelines(&cmds[index]);
	if (!g_err)
	{
		if (!cmds[index + 1])
			return (right);
		else
		{
			type = cmds[index + 1]->word;
			left = and_or(cmds, index + 2);
			if (!ft_strcmp(type, "&&"))
				return (tree(AND, connect(left, right)));
			return (tree(OR, connect(left, right)));
		}
	}
	return (NULL);
}
