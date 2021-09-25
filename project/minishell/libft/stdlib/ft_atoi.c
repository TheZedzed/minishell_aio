/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:17:57 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/16 13:34:36 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	big_num(int len, int nb, int neg, const char *str)
{
	char	*s;

	s = "9223372036854775807";
	if (len > 19)
	{
		if (neg)
			return (0);
		return (-1);
	}
	while (--len && *str++ == *s++)
		;
	if ((len && *str > *s) || !len)
	{
		if (neg)
			return (0);
		return (-1);
	}
	if (neg)
		return (nb);
	return (-nb);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		nb;
	int		len;
	int		neg;

	i = 0;
	nb = 0;
	len = 0;
	neg = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			neg = 1;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = (nb * 10) - (str[i] - '0');
		++i;
		++len;
	}
	if (len >= 19)
		return (big_num(len, nb, neg, str));
	if (neg)
		return (nb);
	return (-nb);
}
