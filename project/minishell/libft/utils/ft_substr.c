/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:37:09 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/16 13:35:11 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	alloc_one(char **res)
{
	(*res) = ft_calloc(1, sizeof(char));
	if (!(*res))
		return (0);
	return (1);
}

static int	alloc_sub(size_t s_len, size_t len, char **res)
{
	if (len > s_len)
		len = s_len;
	(*res) = ft_calloc(len + 1, sizeof(char));
	if (!(*res))
		return (0);
	return (1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*res;
	size_t			s_len;

	i = 0;
	s_len = 0;
	if (s)
		s_len = ft_strlen(s);
	if (!s_len || start >= s_len)
	{
		if (!alloc_one(&res))
			return (NULL);
	}
	else
	{
		if (!alloc_sub(s_len, len, &res))
			return (NULL);
		while (s[start + i] && i < len)
		{
			res[i] = s[start + i];
			++i;
		}
	}
	return (res);
}
