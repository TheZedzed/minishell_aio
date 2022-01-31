/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:19:49 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/29 16:50:11 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	merge(t_tokens **head, t_tokens *list)
{
	t_tokens	*prev;
	t_tokens	*curr;

	if (!g_err)
	{
		prev = NULL;
		curr = (*head);
		while (curr->next)
		{
			prev = curr;
			curr = curr->next;
		}
		if (prev)
			prev->next = list;
		else
			(*head) = list;
	}
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

/*
** Create or update minishell variable
** variable: name + value + scope
*/
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
		curr->value = ft_strdup(value);
		manage_heap(CREATE_VAR, curr->value);
	}
	else
	{
		new = create_var(name, value, scope);
		push_var(head, new);
	}
}
