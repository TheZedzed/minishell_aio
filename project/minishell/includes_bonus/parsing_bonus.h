/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:46:12 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/29 15:24:05 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "parser_utils_bonus.h"

/*
**	AST
*/
t_ast			*parser(t_tokens **token);
t_ast			*tree(int type, void *item);
t_pipeline		*pipe_seq(t_list *sequence);
t_ast			*and_or(t_tokens **cmds, int index);
t_connection	*connect(t_ast *left, t_ast *right);

/*
**	CMD
*/
void			heredoc_(t_cmd *cmd);
void			parse_cmd(t_tokens *seq, t_cmd **head);
void			exec_cmd(void *todo, t_var **vars, int *in);
void			executer(t_ast *todo, t_var **vars, int *in);
char			**cmd_words(t_tokens *list, t_var *vars, int flag);
char			make_redir(t_cmd *cmd, t_var *vars, int *new, int *old);
void			pipex(t_list *cmds, t_var **vars, int size, int *stream);

/*
**	DEBUG
*/
void			show_ast(t_ast *todo);
void			show_command(t_cmd *cmd);

/*
**	UTILS
*/
t_tokens		*last_token(t_tokens *token);
char			*search_ainsi(char *str, int len);
t_var			*search_var(t_var *head, char *name);
void			create_token(t_tokens **list, char *word, int type, int flag);

/*
**	EXPANSION
*/
void			expand(t_tokens **list, t_var *vars, int flag);

/*
**	ENV
*/
char			**update_env(t_var *vars);
int				assign_(char **cmd, t_var **vars, int scope);

/*
**	BUILTIN
*/
int				exit_(char *value);
int				echo_(char **cmd, int *stream);
int				env_(t_var **vars, int flag);
int				unset_(char **names, t_var **vars);
int				cd_(char *path, t_var **vars, char *err);
int				pwd_(t_var **vars, int *stream, char *err);
int				builtin_(char **cmd, t_var **vars, int *stream, char *err);
#endif
