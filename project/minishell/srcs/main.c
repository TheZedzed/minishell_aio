/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:44:46 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/26 13:53:19 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parsing.h"

int			g_err = 0;

static void	create_vars(t_var **head, char **env)
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

static void	lexing(t_tokens **token, t_var **vars)
{
	char	*line;

	line = readline(">");
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
	int			i;

	(void)ac;
	(void)av;
	vars = NULL;
	create_vars(&vars, env);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (g_err <= 0)
	{
		i = 2;
		g_err = 0;
		token = NULL;
		lexing(&token, &vars);
		parsing(&token, &vars);
		while (++i < 1024)
			close(i);
	}
	g_err = ft_atoi(search_var(vars, "?")->value);
	manage_heap(END, NULL);
	write(2, "\nexit\n", 6);
	return (g_err);
}
