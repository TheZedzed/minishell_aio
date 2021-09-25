/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:33:32 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/16 13:32:47 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	res = (char *)haystack;
	if (!*needle)
		return (res);
	while (res[i] && i < len)
	{
		j = 0;
		while (i + j < len && res[i] && res[i + j] == needle[j])
		{
			if (!needle[j + 1])
				return (&res[i]);
			++j;
		}
		++i;
	}
	return (NULL);
}
