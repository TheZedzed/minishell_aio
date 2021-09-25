/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_level.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:40:36 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/28 01:40:49 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	apply_level(t_btree *root, int level, int is_first,
	void (*f)(void *item, int lvl, int first))
{
	if (!root)
		return ;
	if (!level)
		(*f)(root->item, level, is_first);
	else if (level > 0)
	{
		apply_level(root->left, level - 1, is_first, f);
		is_first = 0;
		apply_level(root->right, level - 1, is_first, f);
	}
}

void	btree_apply_by_lvl(t_btree *root, void (*f)(void *item, int i, int j))
{
	int	level;
	int	height;

	level = -1;
	height = btree_level_count(root);
	while (++level < height)
		apply_level(root, level, 1, f);
}
