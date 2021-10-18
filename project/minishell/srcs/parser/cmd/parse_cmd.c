/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 13:09:40 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/31 13:10:21 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	push_words(t_tokens **dest, t_tokens **curr, t_tokens *next)
{
	t_tokens	*tmp;
	int			good;

	tmp = (*dest);
	while (tmp && tmp->next)
		tmp = tmp->next;
	if ((*curr)->type == WORD || (*curr)->type == EXPAND)
		good = 1;
	else if ((*curr)->type == BLANK
		&& (tmp->type == WORD || tmp->type == EXPAND))
		good = 1;
	else
		good = 0;
	if (good)
	{
		push_token(dest, (*curr));
		(*curr)->next = NULL;
	}
	(*curr) = next;
}

static void	push_assign(t_tokens **dest, t_tokens **curr, t_tokens *next)
{
	t_tokens	*tmp;
	char		*res;

	push_token(dest, (*curr));
	(*curr)->next = NULL;
	res = ft_strchr((*curr)->word, '=');
	(*curr) = next;
	if (!*(res + 1))
	{
		while ((*curr))
		{
			next = (*curr)->next;
			if ((*curr)->type == WORD || (*curr)->type == BLANK)
			{
				tmp = next;
				push_token(dest, (*curr));
				(*curr)->next = NULL;
				if ((*curr)->type == BLANK)
					break ;
				(*curr) = tmp;
			}
		}
	}
	(*curr) = next;
}

static void	push_redir(t_tokens **dest, t_tokens **curr, t_tokens *next)
{
	t_tokens	*tmp;

	push_token(dest, (*curr));
	(*curr)->next = NULL;
	if (next->type == BLANK)
		(*curr) = next->next;
	else
		(*curr) = next;
	while ((*curr))
	{
		next = (*curr)->next;
		if ((*curr)->type == WORD || (*curr)->type == BLANK)
		{
			tmp = next;
			push_token(dest, (*curr));
			(*curr)->next = NULL;
			if ((*curr)->type == BLANK)
				break ;
			(*curr) = tmp;
		}
	}
	(*curr) = next;
}

void	parse_cmd(t_tokens *seq, t_cmd **head)
{
	t_tokens	*next;
	t_cmd		*new;

	new = ft_calloc(1, sizeof(t_cmd));
	manage_heap(CREATE_CMD, new);
	if (new)
	{
		while (seq)
		{
			next = seq->next;
			if (!new->words && ft_strchr(seq->word, '=') && is_posix(seq->word))
				push_assign((t_tokens **)&new->assign, &seq, next);
			else if (seq->type == REDIR)
				push_redir((t_tokens **)&new->redir, &seq, next);
			else
				push_words((t_tokens **)&new->words, &seq, next);
		}
		heredoc_(new);
		(*head) = new;
	}
}
