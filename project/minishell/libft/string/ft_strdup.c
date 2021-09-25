/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:18:51 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/16 13:37:45 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	size;

	new = NULL;
	if (s)
	{
		size = ft_strlen(s);
		new = ft_calloc(size + 1, sizeof(char));
		if (!new)
			return (NULL);
		ft_memcpy(new, s, size);
	}
	return (new);
}
