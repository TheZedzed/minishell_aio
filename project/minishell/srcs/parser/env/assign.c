/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:59:56 by azeraoul          #+#    #+#             */
/*   Updated: 2021/10/18 16:59:57 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	local_(t_var **vars, char *name, char *value)
{
	t_var	*res;

	*value = 0;
	res = search_var(*vars, name);
	if (res && !*(value + 1))
		update_var(vars, res->name, "", res->scope);
	else if (!res && !*(value + 1))
		update_var(vars, name, "", LOCAL);
	else if (res && *(value + 1))
		update_var(vars, res->name, value + 1, res->scope);
	else if (!res && *(value + 1))
		update_var(vars, name, value + 1, LOCAL);
}

static void	global_(t_var **vars, char *name, char *value)
{
	t_var	*res;

	res = search_var(*vars, name);
	if (!value && res)
		res->scope = GLOBAL;
	else if (!value && !res)
		update_var(vars, name, "", GLOBAL);
	else if (value)
	{
		*value = 0;
		if (res && !*(value + 1))
			update_var(vars, res->name, "", GLOBAL);
		else if (!res && !*(value + 1))
			update_var(vars, name, "", GLOBAL);
		else if (res && *(value + 1))
			update_var(vars, res->name, value + 1, GLOBAL);
		else if (!res && *(value + 1))
			update_var(vars, name, value + 1, GLOBAL);
	}
}

char	*assign_(char **cmd, t_var **vars, int scope)
{
	char	*res;
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (is_posix(cmd[i]))
		{
			res = ft_strchr(cmd[i], '=');
			if (scope == GLOBAL)
				global_(vars, cmd[i], res);
			else if (scope == LOCAL)
				local_(vars, cmd[i], res);
		}
		else
			return (cmd[i]);
	}
	return (NULL);
}
