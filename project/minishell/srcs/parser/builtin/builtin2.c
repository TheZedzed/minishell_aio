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

static void	save_oldpath(t_var **vars, char *buffer)
{
	t_var	*res;
	int		len;

	res = search_var(*vars, "PWD");
	if (res)
	{
		len = ft_strlen(res->value);
		ft_strcat(buffer, res->value);
		while (len > 1 && buffer[--len] != '/')
			buffer[len] = 0;
		buffer[len] = 0;
		update_var(vars, "PWD", buffer, GLOBAL);
	}
}

static void	go_path(t_var **vars, char *buffer, char *err)
{
	t_var	*new;
	t_var	*old;

	new = search_var(*vars, "PWD");
	if (!new || chdir(new->value))
	{
		old = search_var(*vars, "OLDPWD");
		if (old)
			update_var(vars, "PWD", old->value, GLOBAL);
		if (new)
			perror(new->value);
		*err = '1';
		return ;
	}
	update_var(vars, "PWD", getcwd(buffer, 256), GLOBAL);
}

int	cd_(char *path, t_var **vars, char *err)
{
	char	buffer[256];
	t_var	*pwd;

	ft_memset(buffer, 0, 256);
	update_var(vars, "OLDPWD", getcwd(buffer, 256), GLOBAL);
	if (path)
	{
		pwd = search_var(*vars, "PWD");
		if (pwd && !ft_strcmp(path, "."))
			update_var(vars, "OLDPWD", pwd->value, GLOBAL);
		else if (!ft_strcmp(path, ".."))
			save_oldpath(vars, buffer);
		else
			update_var(vars, "PWD", path, GLOBAL);
		go_path(vars, buffer, err);
	}
	else
	{
		pwd = search_var(*vars, "HOME");
		if (pwd)
			update_var(vars, "PWD", pwd->value, GLOBAL);
	}
	return (1);
}

int	assign_(char **cmd, t_var **vars, int scope)
{
	t_var	*name;
	char	*res;
	int		i;

	i = 0;
	while (cmd[i])
	{
		res = ft_strchr(cmd[i], '=');
		if (res)
			*res = 0;
		name = search_var(*vars, cmd[i]);
		if (name && scope == LOCAL)
			scope = name->scope;
		if (!res || !*(res + 1))
			update_var(vars, cmd[i], "", scope);
		else
			update_var(vars, cmd[i], res + 1, scope);
		++i;
	}
	return (1);
}

int	builtin_(char **cmd, t_var **vars, int *stream, char *err)
{
	char	*name;
	int		flag;

	flag = 0;
	name = cmd[0];
	if (!ft_strcmp(name, "export") && *(cmd + 1) && *(*(cmd + 1)) != '=')
		return (assign_(cmd + 1, vars, GLOBAL));
	else if ((!ft_strcmp(name, "export") && ++flag) || !ft_strcmp(name, "env"))
		return (env_(vars, flag));
	else if (!ft_strcmp(name, "cd"))
		return (cd_(cmd[1], vars, err));
	else if (!ft_strcmp(name, "pwd"))
		return (pwd_(vars, stream, err));
	else if (!ft_strcmp(name, "echo"))
		return (echo_(cmd + 1, stream));
	else if (!ft_strcmp(name, "unset"))
		return (unset_(cmd + 1, vars));
	else if (!ft_strcmp(name, "exit"))
		return (exit_(cmd[1]));
	return (0);
}