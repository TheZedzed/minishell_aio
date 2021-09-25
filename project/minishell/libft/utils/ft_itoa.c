/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:53:56 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/23 11:34:35 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrlen(int nbr)
{
	int		len;

	len = 1;
	if (nbr < 0)
		++len;
	while (nbr >= 10)
	{
		nbr /= 10;
		++len;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		len;
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	len = nbrlen(n);
	num = ft_calloc(len + 1, sizeof(char));
	if (!num)
		return (NULL);
	while (--len >= 0)
	{
		num[len] = 48 + sign * (n % 10);
		n /= 10;
	}
	if (sign < 0)
		num[0] = '-';
	return (num);
}
