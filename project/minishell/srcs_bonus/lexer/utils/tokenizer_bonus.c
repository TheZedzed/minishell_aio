/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:45:30 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/28 01:45:31 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_bonus.h"

static void	set_type(t_tokens *token)
{
	int	c;

	c = token->word[0];
	if (c == 0x28 || c == 0x29)
		token->type = CTRL2;
	else if (c == 0x26 || c == 0x3b || c == 0x7c)
		token->type = CTRL1;
	else if (c == 0x3c || c == 0x3e)
		token->type = REDIR;
	else if (ft_isspace(c))
		token->type = BLANK;
	else
		token->type = WORD;
}

static void	merge(t_tokens **head, t_tokens *list)
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

static void	length(char *beg, int *len)
{
	char	*ptr;

	ptr = beg;
	if (*ptr == 0x24)
	{
		if (spe_var(*(ptr + 1)) || ft_isdigit(*(ptr + 1)))
			ptr += 2;
		else
		{
			while (*++ptr && !special(*ptr))
				;
		}
	}
	else
	{
		while (*ptr && *ptr != 0x22 && *ptr != 0x24)
		{
			if (*ptr == 0x5c)
				++ptr;
			++ptr;
		}
	}
	*len = ptr - beg;
}

static void	rebuild(t_tokens **token, char *word)
{
	t_tokens	*item;
	t_tokens	*new;
	int			len;

	new = NULL;
	while (!g_err && *word != 0x22)
	{
		length(word, &len);
		item = ft_calloc(1, sizeof(t_tokens));
		manage_heap(CREATE_TOK, item);
		if (item)
		{
			push_token(&new, item);
			item->type = WORD;
			item->word = ft_calloc(len + 3, sizeof(char));
			manage_heap(CREATE_WORD, item->word);
			if (item->word)
			{
				ft_memset(item->word, 0x22, len + 2);
				ft_memcpy(item->word + 1, word, len);
				word += len;
			}
		}
	}
	merge(token, new);
}

void	tokenizer(t_tokens **token, char *input)
{
	t_tokens	*new;
	int			len;

	len = 0;
	new = NULL;
	while (!g_err && lexer(&input, &len))
	{
		new = ft_calloc(1, sizeof(t_tokens));
		manage_heap(CREATE_TOK, new);
		if (new)
		{
			push_token(token, new);
			new->word = ft_strndup(input - len, len);
			manage_heap(CREATE_WORD, new->word);
			if (new->word)
			{
				set_type(new);
				if (new->word[0] == 0x22 && ft_strlen(new->word) > 3)
					rebuild(token, &new->word[1]);
			}
		}
		len = 0;
	}
}
