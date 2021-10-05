/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:56:40 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/29 16:56:22 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_BONUS_H
# define PARSER_UTILS_BONUS_H

# include "lexing_bonus.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_ast
{
	int		type;
	void	*item;
}t_ast;

typedef struct s_cmd
{
	int		heredoc;
	void	*redir;
	void	*words;
	void	*assign;
}t_cmd;

typedef struct s_connection
{
	t_ast	*left;
	t_ast	*right;
}t_connection;

typedef struct s_pipeline
{
	t_list	*pipe_sequence;
}t_pipeline;

typedef struct s_ainsi
{
	char	*name;
	int		value;
}t_ainsi;

enum {OR, SUB, CMD, AND, PIPE,
};

typedef struct stat	t_stat;
typedef void	(t_exec)(void *, t_var **, int *);
#endif
