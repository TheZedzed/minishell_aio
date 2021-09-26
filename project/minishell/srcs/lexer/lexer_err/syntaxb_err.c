/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxb_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:17:36 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/25 16:17:37 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	posix_(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c == 0x5f)
		return (1);
	return (0);
}

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
