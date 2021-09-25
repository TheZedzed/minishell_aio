/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:44:56 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/28 01:44:58 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

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

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	spe_var(int c)
{
	static char	*tab = "?@0_#*-$!";

	if (ft_strchr(tab, c))
		return (1);
	return (0);
}

int	skip_blanks(char **str)
{
	while (**str && ft_isspace(**str))
		++*str;
	if (**str)
		return (1);
	return (0);
}

int	special(int c)
{
	static char	*metach = "<>|&;()";
	static char	*escape = "\'\"\\";
	static char	*except = "$\"\\";

	if (ft_strchr(metach, c))
		return (1);
	if (ft_strchr(escape, c))
		return (2);
	if (ft_strchr(except, c))
		return (3);
	if (ft_isspace(c))
		return (4);
	return (0);
}
