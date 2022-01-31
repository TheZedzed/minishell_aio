/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 23:14:04 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/01 23:14:06 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ainsi(char *src)
{
	static t_ainsi	ai[] = {{"a", 0x07}, {"b", 0x08}, {"t", 0x09}, {"n", 0x0a},
							{"v", 0x0b}, {"f", 0x0c}, {"r", 0x0d}, {"\\", 0x5c},
							{"\'", 0x27}, {"\"", 0x22}, {NULL, 0}};
	int				i;
	int				c;

	i = 0;
	while (ai[i].name && ft_strncmp(ai[i].name, src, 1))
		++i;
	if (ai[i].name)
		c = ai[i].value;
	else
		c = src[1];
	return (c);
}

char	*search_ainsi(char *str, int len)
{
	char	tmp[256];
	char	*curr;
	int		i;

	i = -1;
	curr = str + 2;
	ft_memset(tmp, 0, 256);
	while (*curr && *curr != 0x27)
	{
		if (*curr == 0x5c)
		{
			++curr;
			tmp[++i] = ainsi(curr);
		}
		else
			tmp[++i] = *curr;
		++curr;
	}
	ft_memset(str, 0, len - 1);
	ft_strcat(str, tmp);
	return (str);
}

t_var	*search_var(t_var *head, char *name)
{
	while (head)
	{
		if (!ft_strcmp(head->name, name))
			return (head);
		head = head->next;
	}
	return (NULL);
}
