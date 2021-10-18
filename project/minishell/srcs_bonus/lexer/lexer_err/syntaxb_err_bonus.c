/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxb_err_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:15:53 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/25 16:15:54 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_bonus.h"

int	posix_(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c == 0x5f)
		return (1);
	return (0);
}

int	is_posix(char *str)
{
	if (!(ft_isalpha(*str) || *str == 0x5f))
		return (0);
	while (*str && *str != 0x3d)
	{
		if (!posix_(*str))
			return (0);
		++str;
	}
	return (1);
}
