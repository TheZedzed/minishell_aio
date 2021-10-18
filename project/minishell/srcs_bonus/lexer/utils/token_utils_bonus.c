/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:59:40 by azeraoul          #+#    #+#             */
/*   Updated: 2021/10/18 16:59:42 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_bonus.h"

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