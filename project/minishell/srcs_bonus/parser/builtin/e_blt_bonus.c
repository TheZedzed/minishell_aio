/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_blt_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:00:33 by azeraoul          #+#    #+#             */
/*   Updated: 2021/10/18 17:00:35 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static int	exit_err(char *arg, char *err)
{
	write(2, "exit: ", 6);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": numeric argument required\n", 28);
		*err = '2';
	}
	else
	{
		write(2, "too many arguments\n", 19);
		*err = '1';
	}
	return (1);
}

static int	option(char **arg, int *index)
{
	int	opt;
	int	i;
	int	j;

	i = -1;
	opt = 0;
	while (arg[++i])
	{
		if (*arg[i] == 0x2d)
		{
			j = 1;
			while (arg[i][j] && arg[i][j] == 0x6e)
				++j;
			if (!arg[i][j] && ++opt)
				++(*index);
		}
		else
			break ;
	}
	return (opt);
}

int	exit_(char **arg, char *err)
{
	int	res;

	res = 0;
	write(2, "exit\n", 5);
	if (*arg)
	{
		res = ft_atoi(*arg);
		if ((res == -1 && ft_strncmp(*arg, "-1", 3))
			|| (res == 0 && ft_strncmp(*arg, "0", 2)))
		{
			exit_err(*arg, err);
			res = 2;
		}
		else if (*(arg + 1))
			return (exit_err(NULL, err));
	}
	manage_heap(END, NULL);
	exit(res & 0xff);
}

int	echo_(char **cmd)
{
	int	flag;
	int	i;

	i = 0;
	flag = option(cmd, &i);
	while (cmd[i])
	{
		if (*cmd[i])
			printf("%s", cmd[i]);
		if (*cmd[i] && cmd[i + 1])
			printf(" ");
		++i;
	}
	if (!flag)
		printf("\n");
	return (1);
}
