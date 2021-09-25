/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:46:32 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/19 22:48:39 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_BONUS_H
# define LEXING_BONUS_H

# include "lexer_utils_bonus.h"

/*
**	DEBUG
*/
void	show_cmds(t_tokens **cmd);
void	show_tokens(t_tokens *el);

/*
**	LEXER_UTILS
*/
int		spe_var(int c);
int		special(int c);
int		lexer(char **beg, int *len);
void	tokenizer(t_tokens **token, char *input);

/*
**	LEXER_ERR
*/
int		unclosed(char *beg);
int		skip_blanks(char **str);
void	syntax(t_tokens **token, t_var **vars);
void	syntaxb(t_tokens **token, t_var **vars);

/*
**	UTILS
*/
void	handler(int sig);
void	manage_heap(int type, void *addr);
void	push_token(t_tokens **head, t_tokens *new);
void	update_var(t_var **head, char *name, char *value, int scope);
#endif