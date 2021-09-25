/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:41:26 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/28 01:41:27 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_suffix(t_btree *root, void (*f)(void *item))
{
	if (!root)
		return ;
	btree_apply_suffix(root->left, f);
	btree_apply_suffix(root->right, f);
	(*f)(root->item);
}
