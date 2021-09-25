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

#include "lexing_bonus.h"

void	manage_heap(int type, void *addr)
{
	static t_list	*heap;
	t_list			*new;

	if (type == END)
		ft_lstclear(&heap, free);
	else if (!addr)
		g_err = type;
	else
	{
		new = ft_lstnew(addr);
		if (!new)
			g_err = SAVER;
		else
			ft_lstadd_back(&heap, new);
	}
}
