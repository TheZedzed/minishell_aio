/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:46:12 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/29 15:23:41 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "parser_utils.h"

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
char			*search_ainsi(char *str, int len);
t_var			*search_var(t_var *head, char *name);

/*
**	EXPANSION
*/
void			stars_(t_tokens **token);
void			expand(t_tokens **list, t_var *vars, int flag);

/*
**	ENV
*/
char			**update_env(t_var *vars, int empty);
int				assign_(char **cmd, t_var **vars, int scope);

/*
**	BUILTIN
*/

int				echo_(char **arg);
int				exit_(char **arg, char *err);
int				cd_(char **arg, t_var **vars, char *err);
int				builtin_(char **cmd, t_var **vars, char *err);
#endif
