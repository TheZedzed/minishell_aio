/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:43:47 by azeraoul          #+#    #+#             */
/*   Updated: 2021/07/28 01:43:48 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*tree(int type, void *item)
{
	t_ast	*res;

	res = ft_calloc(1, sizeof(t_ast));
	manage_heap(AST_TREE, res);
	if (res)
	{
		res->type = type;
		res->item = item;
	}
	return (res);
}

t_connection	*connect(t_ast *left, t_ast *right)
{
	t_connection	*res;

	res = ft_calloc(1, sizeof(t_connection));
	manage_heap(AST_CONNECTION, res);
	if (res)
	{
		res->left = left;
		res->right = right;
	}
	return (res);
}

t_pipeline	*pipe_seq(t_list *sequence)
{
	t_pipeline	*res;

	res = ft_calloc(1, sizeof(t_pipeline));
	manage_heap(AST_PIPELINES, res);
	if (res)
		res->pipe_sequence = sequence;
	return (res);
}
