/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 00:44:48 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/01 00:49:32 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int	dst_len;
	int	src_len;

	dst_len = 0;
	src_len = 0;
	while (dest[dst_len])
		++dst_len;
	if (src)
	{
		while (src[src_len])
		{
			dest[dst_len + src_len] = src[src_len];
			++src_len;
		}
		dest[dst_len + src_len] = 0;
	}
	return (dest);
}
