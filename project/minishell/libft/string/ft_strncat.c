/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 00:51:59 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/01 00:58:32 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = 0;
	src_len = 0;
	while (dest[dst_len])
		++dst_len;
	while (src[src_len] && src_len < n)
	{
		dest[dst_len + src_len] = src[src_len];
		++src_len;
	}
	dest[dst_len + src_len] = 0;
	return (dest);
}
