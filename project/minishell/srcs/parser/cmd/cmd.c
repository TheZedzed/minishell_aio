/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 19:00:37 by azeraoul          #+#    #+#             */
/*   Updated: 2021/10/05 12:52:56 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**new_cmd(t_tokens *list)
{
	char	**cmd;
	int		size;

	size = 1;
	while (list)
	{
		if (list->type == BLANK)
			++size;
		list = list->next;
	}
	cmd = ft_calloc(size + 1, sizeof(char *));
	manage_heap(CREATE_CMD, cmd);
	return (cmd);
}

static void	one(t_tokens **list, char **cmd, int *index)
{
	char		buffer[4096];
	t_tokens	*curr;

	curr = (*list);
	ft_memset(buffer, 0, 4096);
	while (curr && curr->type != BLANK)
	{
		ft_strcat(buffer, curr->word);
		curr = curr->next;
	}
	cmd[*index] = ft_strdup(buffer);
	manage_heap(CREATE_CMD, cmd[*index]);
	(*list) = curr;
	++*index;
}

char	**cmd_words(t_tokens *list, t_var *vars, int flag)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = NULL;
	if (list)
	{
		if (!ft_strcmp(list->word, "export"))
			flag = ASSIGN;
		if (flag != REDIR)
			expand(&list, vars, flag);
		cmd = new_cmd(list);
		while (list)
		{
			if (list->type != BLANK)
				one(&list, cmd, &i);
			if (list)
				list = list->next;
		}
	}
	return (cmd);
}
