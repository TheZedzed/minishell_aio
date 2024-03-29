/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:45:03 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/28 01:45:04 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

/*
** Manage memory allocation
** use local linked lists of generic pointer
*/
void	manage_heap(int type, void *addr)
{
	static t_list	*heap = NULL;
	static t_list	*vars = NULL;
	t_list			*new;

	if (type == END)
		ft_lstclear(&vars, free);
	else if (type == CLR)
		ft_lstclear(&heap, free);
	else if (!addr)
		g_err = type;
	else
	{
		new = ft_lstnew(addr);
		if (!new)
			g_err = SAVER;
		else if (type == CREATE_VAR)
			ft_lstadd_back(&vars, new);
		else
			ft_lstadd_back(&heap, new);
	}
}
