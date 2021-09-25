/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:44:09 by azeraoul          #+#    #+#             */
/*   Updated: 2021/01/19 17:13:51 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr;
	t_list	*prev;

	prev = NULL;
	curr = lst;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
	}
	return (prev);
}
