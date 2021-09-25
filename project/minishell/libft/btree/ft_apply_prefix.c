/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:41:15 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/28 01:41:16 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_prefix(t_btree *root, void (*f)(void *item))
{
	if (!root)
		return ;
	(*f)(root->item);
	btree_apply_infix(root->left, f);
	btree_apply_infix(root->right, f);
}
