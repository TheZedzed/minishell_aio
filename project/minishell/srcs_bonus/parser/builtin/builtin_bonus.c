/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 18:46:24 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/29 16:50:37 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	exit_(char *value)
{
	int	res;

	res = 0;
	if (value)
		res = ft_atoi(value);
	manage_heap(END, NULL);
	exit(res);
}

int	echo_(char **cmd, int *stream)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	if (*cmd)
	{
		if (!ft_strcmp(cmd[i], "-n") && ++i)
			flag = 1;
		while (cmd[i])
		{
			write(stream[1], cmd[i], ft_strlen(cmd[i]));
			if (cmd[i][0] && cmd[i + 1])
				write(stream[1], " ", 1);
			++i;
		}
	}
	if (!flag)
		write(stream[1], "\n", 1);
	return (1);
}

int	pwd_(t_var **vars, int *stream, char *err)
{
	char	*res;

	res = search_var(*vars, "PWD")->value;
	if (res)
	{
		write(stream[1], res, ft_strlen(res));
		write(stream[1], "\n", 1);
	}
	else
		*err = '1';
	return (1);
}

int	unset_(char **cmd, t_var **vars)
{
	t_var	*prev;
	t_var	*curr;
	char	*name;

	name = *cmd;
	while (*name)
	{
		curr = *vars;
		while (curr && ft_strcmp(curr->name, name))
		{
			prev = curr;
			curr = curr->next;
		}
		if (curr)
			prev->next = curr->next;
		++name;
	}
	return (1);
}

int	env_(t_var **vars, int flag)
{
	t_var	*curr;

	curr = *vars;
	while (curr)
	{
		if (curr->scope == GLOBAL)
		{
			if (flag)
				printf("declare -x %s=\"%s\"\n", curr->name, curr->value);
			else if (*curr->value)
				printf("%s=%s\n", curr->name, curr->value);
		}
		curr = curr->next;
	}
	return (1);
}
