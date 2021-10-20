/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:58:16 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/29 16:55:34 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_BONUS_H
# define LEXER_UTILS_BONUS_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CD_ERR "cd: error retrieving current directory: getcwd: \
cannot access parent directories: "

extern int	g_err;

typedef struct s_tokens {
	int				type;
	char			*word;
	struct s_tokens	*next;
}t_tokens;

typedef struct s_var {
	int				scope;
	char			*name;
	char			*value;
	struct s_var	*next;
}t_var;

enum {LOCAL, GLOBAL
};

enum {BLANK, WORD, EXPAND, REDIR, CTRL1, CTRL2, ASSIGN,
};

enum {
	HERE = -5,
	SYNTAX = -4,
	FEATURE = -3,
	UNCLOSED = -2,
	INPUT_ERR = -1,
	END = 0,
	SAVER = 1,
	INPUT = 2,
	CREATE_TOK = 3,
	CREATE_WORD = 4,
	AST_TREE = 5,
	AST_CONNECTION = 6,
	AST_PIPELINES = 7,
	PIPELINE = 8,
	SEPARE_CMDS = 9,
	CREATE_VAR = 10,
	CREATE_ENV = 11,
	CREATE_CMD = 12
};
#endif
