/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:41:04 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/28 01:41:06 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_infix(t_btree *root, void (*f)(void *item))
{
	if (!root)
		return ;
	btree_apply_infix(root->left, f);
	(*f)(root->item);
	btree_apply_infix(root->right, f);
}
