/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:06:34 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/16 13:30:56 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*psrc;
	unsigned char		*pdst;

	psrc = (const unsigned char *)src;
	pdst = (unsigned char *)dst;
	if (psrc != pdst)
	{
		if (psrc < pdst && pdst < psrc + len)
		{
			psrc += len;
			pdst += len;
			while (len--)
				*--pdst = *--psrc;
		}
		else
		{
			while (len--)
				*pdst++ = *psrc++;
		}
	}
	return (dst);
}
