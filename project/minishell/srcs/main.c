/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:44:46 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/19 22:17:22 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parsing.h"

int			g_err = 0;

/*
** Minishell env
*/
static void	create_env(t_var **head, char **env)
{
	char	*res;
	int		i;

	i = 0;
	while (env[i])
	{
		res = ft_strchr(env[i], '=');
		*res = 0;
		update_var(head, env[i], res + 1, GLOBAL);
		++i;
	}
	update_var(head, "?", "0", LOCAL);
}

/*
** Create AST then execute it
*/
static void	parsing(t_tokens **token, t_var **vars)
{
	t_ast	*todo;
	int		stream[3];

	todo = NULL;
	stream[2] = -1;
	stream[0] = STDIN_FILENO;
	stream[1] = STDOUT_FILENO;
	if (!g_err)
	{
		todo = parser(token);
		if (!g_err)
			executer(todo, vars, stream);
	}
}

/*
** Read input line
** Add to history
** Check line syntax
*/
static void	lexing(t_tokens **token, t_var **vars)
{
	char	*line;

	line = readline("zZz-minishell>");
	manage_heap(INPUT, line);
	if (!line)
		g_err = INPUT;
	else
	{
		if (*line)
			add_history(line);
		skip_blanks(&line);
		if (!unclosed(line))
		{
			tokenizer(token, line);
			syntax(token, vars);	
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_tokens	*token;
	t_var		*vars;

	(void)ac;
	(void)av;
	vars = NULL;
	create_env(&vars, env);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (g_err <= 0)
	{
		g_err = 0;
		token = NULL;
		lexing(&token, &vars);
		parsing(&token, &vars);
		for (int i = 3; i < MAX_FD; ++i)
			close(i);
		manage_heap(CLR, NULL);
	}
	g_err = ft_atoi(search_var(vars, "?")->value);
	manage_heap(END, NULL);
	write(2, "\nexit\n", 6);
	return (g_err);
}
