/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:35:25 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/03 17:35:27 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static void	swap_(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	env_size(t_var *vars)
{
	int	size;

	size = 0;
	while (vars)
	{
		if (vars->scope == GLOBAL)
			++size;
		vars = vars->next;
	}
	return (size);
}

static void	sort_(char **cmd)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (cmd[i])
	{
		j = i + 1;
		while (cmd[j])
		{
			if (*cmd[i] > *cmd[j])
				swap_(&cmd[i], &cmd[j]);
			else if (*cmd[i] == *cmd[j])
			{
				k = 0;
				while (cmd[i][k] && cmd[j][k] && cmd[i][k] == cmd[j][k])
					++k;
				if (cmd[i][k] && cmd[i][k] > cmd[j][k])
					swap_(&cmd[i], &cmd[j]);
			}
			++j;
		}
		++i;
	}
}

static char	**init_env(t_var *vars, int export)
{
	char	**env;
	int		cpt[3];

	cpt[0] = 0;
	env = ft_calloc(env_size(vars) + 1, sizeof(char *));
	manage_heap(CREATE_ENV, env);
	while (!g_err && vars)
	{
		if (vars->scope == GLOBAL && ((*vars->value && !export) || export))
		{
			cpt[1] = ft_strlen(vars->name);
			cpt[2] = ft_strlen(vars->value);
			env[cpt[0]] = ft_calloc(cpt[1] + cpt[2] + 5, sizeof(char));
			manage_heap(CREATE_ENV, env[cpt[0]]);
			++cpt[0];
		}
		vars = vars->next;
	}
	return (env);
}

char	**update_env(t_var *vars, int export)
{
	char	**tab;
	int		i;

	i = -1;
	tab = init_env(vars, export);
	while (!g_err && vars)
	{
		if (vars->scope == GLOBAL && ((*vars->value && !export) || export))
		{
			ft_strcat(tab[++i], vars->name);
			if (*vars->value && ft_strcat(tab[i], "="))
			{
				if (export)
					ft_strcat(tab[i], "\"");
				if (ft_strcmp(vars->value, "="))
					ft_strcat(tab[i], vars->value);
				if (export)
					ft_strcat(tab[i], "\"");
			}	
		}
		vars = vars->next;
	}
	if (export)
		sort_(tab);
	return (tab);
}
