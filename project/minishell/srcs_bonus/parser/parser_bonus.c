/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:44:37 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/28 01:44:38 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static void	swap_cmds(t_tokens **a, t_tokens **b)
{
	t_tokens	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	reverse_cmds(t_tokens **cmds)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (cmds[i])
	{
		++i;
		++size;
	}
	i = -1;
	while (++i < --size)
		swap_cmds(&cmds[i], &cmds[size]);
}

static void	pipelines_cmd(t_tokens **list, t_tokens **cmds, int *index)
{
	t_tokens	*last;
	t_tokens	*new;

	while ((*list) && ft_strcmp((*list)->word, "&&")
		&& ft_strcmp((*list)->word, "||"))
	{
		new = (*list);
		if (new->type == CTRL2)
		{
			last = last_token(new);
			while ((*list) != last->next)
				(*list) = (*list)->next;
			last->next = NULL;
			push_token(&cmds[*index], new);
		}
		else
		{
			push_token(&cmds[*index], new);
			(*list) = (*list)->next;
			new->next = NULL;
		}
	}
}

static void	separe_cmds(t_tokens **cmds, t_tokens **list)
{
	t_tokens	*new;
	char		*word;
	int			i;

	i = 0;
	while ((*list))
	{
		word = (*list)->word;
		if (!ft_strcmp(word, "&&") || !ft_strcmp(word, "||"))
		{
			new = (*list);
			(*list) = (*list)->next;
			new->next = NULL;
			if ((*list)->type == BLANK)
				(*list) = (*list)->next;
			push_token(&cmds[i], new);
		}
		else
			pipelines_cmd(list, cmds, &i);
		++i;
	}
}

t_ast	*parser(t_tokens **token)
{
	t_ast		*ast;
	t_tokens	**cmds;

	ast = NULL;
	cmds = ft_calloc(30, sizeof(t_tokens *));
	manage_heap(SEPARE_CMDS, cmds);
	if (cmds)
	{
		separe_cmds(cmds, token);
		reverse_cmds(cmds);
		ast = and_or(cmds, 0);
	}
	return (ast);
}
