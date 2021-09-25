/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:03:10 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/16 13:32:35 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char c, char const *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

static size_t	trimmed_str(char const *s1, char const *set)
{
	char		*beg;
	char		*end;
	size_t		len;

	len = ft_strlen(s1);
	end = (char *)(s1 + len - 1);
	beg = (char *)s1;
	while (is_in(*beg, set))
	{
		++beg;
		--len;
	}
	while (len && is_in(*end, set))
	{
		--end;
		--len;
	}
	return (len);
}

char	*ft_ncpy(char *dest, char const *s1, size_t n)
{
	size_t		i;

	i = 0;
	while (s1[i] && i < n)
	{
		dest[i] = s1[i];
		++i;
	}
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	size_t		len;

	if (!set || !s1)
		return (NULL);
	len = trimmed_str(s1, set);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (is_in(*s1, set))
		++s1;
	ft_ncpy(res, s1, len);
	return (res);
}
