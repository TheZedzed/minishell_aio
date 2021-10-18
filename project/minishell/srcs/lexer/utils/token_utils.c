/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:59:40 by azeraoul          #+#    #+#             */
/*   Updated: 2021/10/18 16:59:42 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	posix_(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c == 0x5f)
		return (1);
	return (0);
}

int	is_posix(char *str)
{
	if (!(ft_isalpha(*str) || *str == 0x5f))
		return (0);
	while (*str && *str != 0x3d)
	{
		if (!posix_(*str))
			return (0);
		++str;
	}
	return (1);
}

void	create_token(t_tokens **list, char *word, int type)
{
	t_tokens	*new;

	new = ft_calloc(1, sizeof(t_tokens));
	manage_heap(CREATE_CMD, new);
	if (new)
	{
		new->type = type;
		new->word = ft_strdup(word);
		manage_heap(CREATE_CMD, new->word);
		push_token(list, new);
	}
}

t_tokens	*last_token(t_tokens *token)
{
	int	countl;
	int	countr;

	countl = 0;
	countr = 0;
	while (token)
	{
		if (!ft_strcmp(token->word, "("))
			++countl;
		else if (!ft_strcmp(token->word, ")"))
			++countr;
		if (countr == countl)
			break ;
		token = token->next;
	}
	return (token);
}

void	push_token(t_tokens **head, t_tokens *new)
{
	t_tokens	*curr;

	if (head)
	{
		if (!(*head))
			(*head) = new;
		else
		{
			curr = (*head);
			while (curr->next)
				curr = curr->next;
			curr->next = new;
		}
	}
}
