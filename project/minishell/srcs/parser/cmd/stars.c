/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:00:13 by azeraoul          #+#    #+#             */
/*   Updated: 2021/10/18 17:00:14 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_tokens	*last(t_tokens *token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

static void	create(t_tokens **list, char *name)
{
	if (*name != '.')
	{
		create_token(list, name, WORD);
		create_token(list, " ", BLANK);
	}
}

static void	reader(t_tokens **tokens, t_tokens *prev, t_tokens *next)
{
	struct dirent	*files;
	t_tokens		*new;
	DIR				*dir;

	new = NULL;
	dir = opendir(".");
	if (prev)
	{
		prev->next = NULL;
		create_token(&new, " ", BLANK);
	}
	while (1)
	{
		files = readdir(dir);
		if (files)
			create(&new, files->d_name);
		else
			break ;
	}
	closedir(dir);
	merge(tokens, new);
	last(*tokens)->next = next;
}

void	stars_(t_tokens **token)
{
	t_tokens	*curr;
	t_tokens	*prev;
	t_tokens	*next;
	char		*word;

	if (token)
	{
		prev = NULL;
		curr = *token;
		while (curr)
		{
			next = curr->next;
			word = curr->word;
			if (*word == 0x2a)
			{
				while (*word && *word == 0x2a)
					++word;
				if (!*word)
					reader(token, prev, next);
			}
			prev = curr;
			curr = next;
		}
	}
}
