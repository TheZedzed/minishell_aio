/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 18:46:24 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/29 15:38:35 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static int	pwd_(void)
{
	char	buffer[4096];

	ft_memset(buffer, 0, 4096);
	if (getcwd(buffer, 4095))
		printf("%s\n", buffer);
	else
		perror(CD_ERR);
	return (1);
}

static int	unset_(char **cmd, t_var **vars)
{
	t_var	*prev;
	t_var	*curr;
	int		i;

	i = 0;
	while (cmd[i])
	{
		curr = *vars;
		while (curr && ft_strcmp(curr->name, cmd[i]))
		{
			prev = curr;
			curr = curr->next;
		}
		if (curr)
			prev->next = curr->next;
		++i;
	}
	return (1);
}

static int	export_(char **arg, t_var **vars, char *err)
{
	int	i;

	if (!*arg)
	{
		i = -1;
		arg = update_env(*vars, 1);
		while (arg[++i])
			printf("declare -x %s\n", arg[i]);
	}
	else
		*err = assign_(arg, vars, GLOBAL) + 48;
	return (1);
}

int	builtin_(char **cmd, t_var **vars, char *err)
{
	char	*name;

	name = cmd[0];
	if (!ft_strcmp(name, "export"))
		return (export_(cmd + 1, vars, err));
	else if (!ft_strcmp(name, "cd"))
		return (cd_(cmd + 1, vars, err));
	else if (!ft_strcmp(name, "pwd"))
		return (pwd_());
	else if (!ft_strcmp(name, "echo"))
		return (echo_(cmd + 1));
	else if (!ft_strcmp(name, "unset"))
		return (unset_(cmd + 1, vars));
	else if (!ft_strcmp(name, "exit"))
		return (exit_(cmd + 1, err));
	return (0);
}
