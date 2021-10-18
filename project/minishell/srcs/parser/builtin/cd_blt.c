/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 18:14:58 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/25 16:16:43 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	cd_err(int num, char *arg, char *err)
{
	if (!num)
		write(2, "cd: too many arguments\n", 23);
	else if (num == 1)
		write(2, "HOME not set\n", 13);
	else if (num == 2)
	{
		write(2, "cd: ", 4);
		write(2, arg, ft_strlen(arg));
		write(2, ": No such file or directory\n", 28);
	}
	else
		perror(CD_ERR);
	*err = '1';
	return (1);
}

static void	save_(t_var **vars, int oldpwd, char *pwd)
{
	t_var	*curr;
	t_var	*old;

	curr = search_var(*vars, "PWD");
	old = search_var(*vars, "OLDPWD");
	if (oldpwd)
	{
		if (curr && old)
			update_var(vars, "OLDPWD", curr->value, old->scope);
		else if (curr && !old)
			update_var(vars, "OLDPWD", curr->value, LOCAL);
		else if (!curr && old)
			update_var(vars, "OLDPWD", "", old->scope);
		else
			update_var(vars, "OLDPWD", "", LOCAL);
	}
	else if (curr)
		update_var(vars, "PWD", pwd, curr->scope);
	else
		update_var(vars, "PWD", pwd, LOCAL);
}

int	cd_(char **arg, t_var **vars, char *err)
{
	char	buffer[256];
	char	*pwd;

	if (*arg && *(arg + 1))
		return (cd_err(0, NULL, err));
	else if (*arg)
		pwd = *arg;
	else
	{
		if (!search_var(*vars, "HOME"))
			return (cd_err(1, NULL, err));
		pwd = search_var(*vars, "HOME")->value;
	}
	save_(vars, 1, NULL);
	if (chdir(pwd))
		return (cd_err(2, pwd, err));
	ft_memset(buffer, 0, 256);
	pwd = getcwd(buffer, 256);
	if (!pwd)
		return (cd_err(3, NULL, err));
	save_(vars, 0, pwd);
	return (1);
}
