/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:43:27 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/28 01:43:28 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_bonus.h"

static void	skip_quoted(char **beg, int c)
{
	int	pass;

	pass = 0;
	while (**beg)
	{
		if (**beg == c)
			++pass;
		if (pass == 2)
			break ;
		else if (**beg == 0x5c && c == 0x22)
			++*beg;
		++*beg;
	}
}

static void	unclosed_paran(char *beg, int *c)
{
	int	countr;
	int	countl;

	countr = 0;
	countl = 0;
	while (!g_err && *beg)
	{
		if (*beg == 0x28 || *beg == 0x29)
		{
			*c = *beg;
			if (*beg == 0x28)
				++countr;
			else
				++countl;
		}
		else if (*beg == 0x22 || *beg == 0x27)
			skip_quoted(&beg, *beg);
		++beg;
	}
	if (countr != countl)
		g_err = INPUT_ERR;
}

static void	unclosed_quote(char *beg, int *c)
{
	int	pass;

	while (!g_err && *beg)
	{
		if (*beg == 0x5c)
			beg += 2;
		else if (*beg == 0x22 || *beg == 0x27)
		{
			pass = 0;
			*c = *beg;
			while (*beg && pass < 2)
			{
				if (*beg == *c)
					++pass;
				else if (*beg == 0x5c && *c == 0x22)
					++beg;
				++beg;
			}
			if (!*beg && pass != 2)
				g_err = INPUT_ERR;
		}
		else
			++beg;
	}
}

static void	unclosed_slash(char *beg, int *c)
{
	while (!g_err && *beg)
	{
		if (*beg == 0x5c)
		{
			*c = *beg;
			if (!*++beg)
				g_err = INPUT_ERR;
			else
				++beg;
		}
		else
			++beg;
	}
}

int	unclosed(char *beg)
{
	int	c;

	c = 0;
	if (!*beg)
		g_err = INPUT_ERR;
	else
	{
		unclosed_slash(beg, &c);
		unclosed_quote(beg, &c);
		unclosed_paran(beg, &c);
	}
	if (g_err && c)
	{
		printf("error -- unclosed: [%c]\n", c);
		return (1);
	}
	return (0);
}
