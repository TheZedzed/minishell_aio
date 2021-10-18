/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:45:43 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/29 03:34:18 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	quote_removal(char *str, int d)
{
	char	buffer[4096];
	char	*ptr;
	int		c;
	int		i;

	if (ft_strlen(str) > 1 && (d == 0x22 || d == 0x27))
	{
		i = 0;
		ptr = str + 1;
		while (*ptr && *ptr != d)
		{
			if (*ptr == 0x5c && d == 0x22)
			{
				c = *(ptr + 1);
				if (c == 0x22 || c == 0x24 || c == 0x5c)
					++ptr;
			}
			buffer[i] = *ptr;
			++ptr;
			++i;
		}
		buffer[i] = 0;
		ft_memcpy(str, buffer, ft_strlen(buffer) + 1);
	}
}

static void	simple_expand(t_tokens *token, t_var *vars)
{
	t_var	*res;
	char	*word;
	int		len;

	word = token->word;
	len = ft_strlen(word);
	res = search_var(vars, word);
	if (res)
	{
		token->word = ft_strdup(res->value);
		manage_heap(CREATE_VAR, token->word);
	}
	else
		ft_memset(word, 0, len);
	quote_removal(token->word, *token->word);
}

static void	split_expand(t_tokens **list, char *word)
{
	char	buffer[4096];
	char	*curr;
	char	*beg;

	curr = buffer;
	ft_memset(buffer, 0, 4096);
	ft_strcat(buffer, word);
	quote_removal(buffer, *buffer);
	while (!g_err && *curr)
	{
		beg = curr;
		while (*curr && !ft_isspace(*curr))
			++curr;
		if (*curr)
		{
			while (*curr && ft_isspace(*curr))
				*curr++ = 0;
			create_token(list, beg, WORD);
			create_token(list, " ", BLANK);
		}
	}
	create_token(list, beg, WORD);
}

static void	word_splitting(t_tokens **list, t_tokens *tok, t_var *vars)
{
	t_tokens	*curr;
	t_tokens	*new;
	t_var		*res;

	new = NULL;
	curr = (*list);
	res = search_var(vars, tok->word);
	if (res && res->value && *res->value)
		split_expand(&new, res->value);
	else
		create_token(&new, "", WORD);
	if (tok == (*list))
		(*list) = new;
	else
	{
		while (curr && curr->next != tok)
			curr = curr->next;
		curr->next = new;
	}
	curr = new;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = tok->next;
}

void	expand(t_tokens **list, t_var *vars, int flag)
{
	t_tokens	*tok;
	int			len;

	tok = *list;
	stars_(list);
	while (tok)
	{
		len = ft_strlen(tok->word);
		if (!ft_strncmp(tok->word, "$\'", 2))
			search_ainsi(tok->word, len);
		else if (tok->type == EXPAND && flag != ASSIGN)
			word_splitting(list, tok, vars);
		else if (tok->type == EXPAND && flag == ASSIGN)
			simple_expand(tok, vars);
		else
			quote_removal(tok->word, *tok->word);
		tok = tok->next;
	}
}
