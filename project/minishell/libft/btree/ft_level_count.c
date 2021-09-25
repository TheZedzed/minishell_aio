/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:39:34 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/28 01:39:36 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	btree_level_count(t_btree *root)
{
	int	countl;
	int	countr;

	countl = 0;
	countr = 0;
	if (!root)
		return (0);
	if (root->left)
		countl = btree_level_count(root->left);
	if (root->right)
		countr = btree_level_count(root->right);
	if (countl > countr)
		return (countl + 1);
	return (countr + 1);
}
