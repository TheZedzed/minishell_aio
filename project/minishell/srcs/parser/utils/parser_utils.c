/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:19:49 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/29 03:33:06 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	create_token(t_tokens **list, char *word, int type, int flag)
{
	t_tokens	*new;

	new = ft_calloc(1, sizeof(t_tokens));
	manage_heap(CREATE_CMD, new);
	if (new)
	{
		new->type = type;
		if (flag)
		{
			new->word = ft_strdup(word);
			manage_heap(CREATE_CMD, new->word);
		}
		else
			new->word = word;
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

static void	push_var(t_var **head, t_var *new)
{
	t_var	*curr;

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

static t_var	*create_var(char *name, char *value, int scope)
{
	t_var	*new;

	new = ft_calloc(1, sizeof(t_var));
	manage_heap(CREATE_VAR, new);
	if (new)
	{
		new->scope = scope;
		new->name = ft_strdup(name);
		new->value = ft_strdup(value);
		manage_heap(CREATE_VAR, new->value);
		manage_heap(CREATE_VAR, new->name);
	}
	return (new);
}

void	update_var(t_var **head, char *name, char *value, int scope)
{
	t_var	*curr;
	t_var	*new;

	curr = *head;
	while (curr && ft_strcmp(curr->name, name))
		curr = curr->next;
	if (curr)
	{
		curr->scope = scope;
		if (*value && ft_strcmp(curr->value, value))
		{
			curr->value = ft_strdup(value);
			manage_heap(CREATE_VAR, curr->value);
		}
	}
	else
	{
		new = create_var(name, value, scope);
		push_var(head, new);
	}
}
