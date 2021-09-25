/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxb_err_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:15:53 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/25 16:15:54 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_bonus.h"

void	syntaxb(t_tokens **token, t_var **vars)
{
	t_tokens	*curr;

	curr = (*token);
	if (g_err)
		return ;
	while (curr)
	{
		if (curr->type == WORD && !ft_strcmp(curr->word, "export"))
		{
			curr = curr->next;
			if (curr->type == BLANK)
				curr = curr->next;
			if (curr && curr->type == WORD && *curr->word == '=')
			{
				g_err = SYNTAX;
				printf("export: `%s': not a valid identifier\n", curr->word);
				update_var(vars, "?", "1", LOCAL);
			}
		}
		curr = curr->next;
	}
}
