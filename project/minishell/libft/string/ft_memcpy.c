/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:05:03 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/16 13:32:08 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*psrc;
	unsigned char		*pdst;

	pdst = (unsigned char *)dst;
	psrc = (const unsigned char *)src;
	if (dst != src)
	{
		while (n)
		{
			*pdst = *psrc;
			++pdst;
			++psrc;
			--n;
		}
	}
	return (dst);
}
