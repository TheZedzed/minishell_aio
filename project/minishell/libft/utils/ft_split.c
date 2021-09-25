/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:16:29 by azeraoul          #+#    #+#             */
/*   Updated: 2021/05/11 22:22:07 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		++i;
	}
	free(tab);
	return (NULL);
}

static int	ft_nb_words(const char *str, char c)
{
	int		words;

	words = 0;
	while (*str)
	{
		if (*str != c)
		{
			++words;
			while (*str && *str != c)
				++str;
		}
		else
			++str;
	}
	return (words);
}

static char	*word(const char *str, char c)
{
	char	*res;
	int		len;

	len = 0;
	while (str[len] && str[len] != c)
		++len;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != c)
	{
		res[len] = str[len];
		++len;
	}
	return (res);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		nb_words;
	int		i;

	i = 0;
	nb_words = ft_nb_words(s, c);
	tab = ft_calloc(nb_words + 1, sizeof(char *));
	if (!s || !tab)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			++s;
		if (*s && *s != c)
		{
			tab[i] = word(s, c);
			if (!tab[i])
				return (free_all(tab));
			while (*s && *s != c)
				++s;
			++i;
		}
	}
	return (tab);
}
