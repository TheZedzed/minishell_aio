/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:21:24 by azeraoul          #+#    #+#             */
/*   Updated: 2021/01/19 17:25:33 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*prev;

	if (lst)
	{
		prev = NULL;
		curr = (*lst);
		while (curr)
		{
			prev = curr;
			curr = curr->next;
			ft_lstdelone(prev, del);
		}
		(*lst) = NULL;
	}
}
