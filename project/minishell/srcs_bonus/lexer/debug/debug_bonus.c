/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 13:18:04 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/31 13:18:05 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	show_command(t_cmd *cmd)
{
	t_tokens	*r;
	t_tokens	*a;
	t_tokens	*w;

	r = cmd->redir;
	printf("redir:");
	while (r)
	{
		printf(" [%s]", r->word);
		r = r->next;
	}
	a = cmd->assign;
	printf("\nassign:");
	while (a)
	{
		printf(" [%s]", a->word);
		a = a->next;
	}
	w = cmd->words;
	printf("\ncmd:");
	while (w)
	{
		printf(" [%s]", w->word);
		w = w->next;
	}
}

void	show_tokens(t_tokens *el)
{
	t_tokens	*curr;

	curr = el;
	while (curr)
	{
		printf("[%s, %d] ", curr->word, curr->type);
		curr = curr->next;
	}
	if (el)
		printf("\n");
}

void	show_cmds(t_tokens **cmds)
{
	int	index;

	index = 0;
	while (cmds[index])
	{
		show_tokens(cmds[index]);
		++index;
	}
}
