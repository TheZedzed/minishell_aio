/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:44:11 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/28 01:44:12 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_bonus.h"

static int	lexe_simple(char **beg, int *len)
{
	char	*ptr;

	ptr = *beg;
	while (**beg && !special(**beg))
		++*beg;
	*len = *beg - ptr;
	return (lexer(beg, len));
}

static int	lexe_dollar(char **beg, int *len)
{
	char	*ptr;
	int		pass;

	pass = 0;
	ptr = *beg;
	if (*(ptr + 1) == 0x22 && ++*beg)
		return (lexer(beg, len));
	if (*(ptr + 1) == 0x27)
	{
		while (*(++*beg) && pass < 2)
		{
			if (**beg == 0x27)
				++pass;
		}
	}
	else if (*(ptr + 1) && (spe_var(*(ptr + 1)) || ft_isdigit(*(ptr + 1))))
		*beg += 2;
	else
	{
		while (*(++*beg) && posix_(**beg))
			;
	}
	*len = *beg - ptr;
	return (lexer(beg, len));
}

static int	lexe_escape(char **beg, int *len)
{
	char	*ptr;
	int		pass;
	int		c;

	pass = 0;
	c = **beg;
	ptr = *beg;
	if (c == 0x5c)
		*len = ++*beg - ptr;
	else
	{
		while (**beg && (**beg != c || !pass))
		{
			pass = 1;
			if (**beg == 0x5c && c == 0x22)
				*beg += 2;
			else
				*beg += 1;
		}
		*len = *beg - ptr + 1;
	}
	++*beg;
	return (lexer(beg, len));
}

static int	lexe_metach(char **beg, int *len)
{
	char	*ptr;
	int		count;
	int		c;

	count = 0;
	c = **beg;
	ptr = *beg;
	if (c == 0x28 || c == 0x29)
		++*beg;
	else
	{
		while (**beg && special(**beg) == 1 && count != 3)
		{
			++count;
			if (**beg == 0x28 || **beg == 0x29)
				break ;
			++*beg;
		}
	}
	*len = *beg - ptr;
	return (lexer(beg, len));
}

int	lexer(char **beg, int *len)
{
	int	res;

	if (g_err || !**beg || *len)
		return (0);
	res = special(**beg);
	if (!res)
		return (1 + lexe_simple(beg, len));
	else if (res == 1)
		return (1 + lexe_metach(beg, len));
	else if (res == 2)
		return (1 + lexe_escape(beg, len));
	else if (res == 3)
		return (1 + lexe_dollar(beg, len));
	*len = skip_blanks(beg);
	return (*len + lexer(beg, len));
}
