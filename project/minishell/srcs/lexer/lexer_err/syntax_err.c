/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:44:25 by azeraoul          #+#    #+#             */
/*   Updated: 2021/10/05 10:19:06 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static int	unsupported(char *str)
{
	static char	*cntrl[] = {"&&", "|", "||", "(", ")", NULL};
	static char	*redir[] = {"<", "<<", ">", ">>", NULL};
	int			res;
	int			i;

	i = 0;
	res = 42;
	while (res && cntrl[i])
	{
		res = ft_strcmp(str, cntrl[i]);
		++i;
	}
	i = 0;
	while (res && redir[i])
	{
		res = ft_strcmp(str, redir[i]);
		++i;
	}
	return (res);
}

static void	err_msg(t_tokens *curr, t_var **vars)
{
	char	*str;

	if (curr->type == REDIR)
		curr = curr->next;
	if (!curr)
		str = "newline";
	else
	{
		if (curr->type == BLANK)
			curr = curr->next;
		str = curr->word;
	}
	if (g_err == SYNTAX)
		printf("minishell: syntax error near unexpected token `%s'\n", str);
	else if (g_err == UNCLOSED)
		printf("error -- unclosed: [%s]\n", str);
	else if (g_err == FEATURE)
		printf("error -- feature not supported near token `%s'\n", str);
	if (g_err)
		update_var(vars, "?", "2", LOCAL);
}

static void	syntax_cntrl(t_tokens *curr, t_tokens *prev)
{
	char	*str;
	int		type;

	str = curr->word;
	type = curr->type;
	if (unsupported(str))
		g_err = FEATURE;
	else
	{
		if (type == CTRL1)
		{
			if (!prev || prev->type == CTRL1 || !ft_strcmp(prev->word, "("))
				g_err = SYNTAX;
			else if (!curr->next)
				g_err = UNCLOSED;
		}
		else if (!ft_strcmp(str, "(") && prev && (prev->type == WORD
				|| !ft_strcmp(prev->word, "(")))
			g_err = FEATURE;
		else if (!ft_strcmp(str, ")") && prev
			&& (prev->type == CTRL1 || !ft_strcmp(prev->word, "(")))
			g_err = SYNTAX;
	}
}

static void	syntax_redir(t_tokens *curr)
{
	char	*str;

	str = curr->word;
	if (unsupported(str))
		g_err = FEATURE;
	else
	{
		curr = curr->next;
		while (curr)
		{
			if (curr->type != BLANK)
				break ;
			curr = curr->next;
		}
		if (!curr || curr->type != WORD)
			g_err = SYNTAX;
	}
}

/*
** Chex tokens syntax rule
*/
void	syntax(t_tokens **token, t_var **vars)
{
	t_tokens	*curr;
	t_tokens	*prev;

	prev = NULL;
	curr = (*token);
	while (!g_err && curr)
	{
		if (curr->type == REDIR)
			syntax_redir(curr);
		else if (curr->type == CTRL1 || curr->type == CTRL2)
			syntax_cntrl(curr, prev);
		else if (curr->type == WORD && prev && !ft_strcmp(prev->word, ")"))
			g_err = SYNTAX;
		if (curr->type != BLANK)
			prev = curr;
		if (g_err)
			err_msg(curr, vars);
		else
			curr = curr->next;
	}
}
