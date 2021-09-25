/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:35:25 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/03 17:35:27 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

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

static char	**init_env(t_var *vars)
{
	char	**env;
	int		len1;
	int		len2;
	int		i;

	i = 0;
	env = ft_calloc(env_size(vars) + 1, sizeof(char *));
	manage_heap(CREATE_ENV, env);
	while (!g_err && vars)
	{
		if (vars->scope == GLOBAL)
		{
			len1 = ft_strlen(vars->name);
			len2 = ft_strlen(vars->value);
			env[i] = ft_calloc(len1 + len2 + 2, sizeof(char));
			manage_heap(CREATE_ENV, env[i]);
			++i;
		}
		vars = vars->next;
	}
	return (env);
}

char	**update_env(t_var *vars)
{
	char	**tab;
	int		i;

	i = 0;
	tab = init_env(vars);
	while (!g_err && vars)
	{
		if (vars->scope == GLOBAL)
		{
			ft_strcat(tab[i], vars->name);
			ft_strcat(tab[i], "=");
			if (vars->value)
				ft_strcat(tab[i], vars->value);
			++i;
		}
		vars = vars->next;
	}
	return (tab);
}
