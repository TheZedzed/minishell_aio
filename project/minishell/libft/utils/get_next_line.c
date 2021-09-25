/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 01:07:37 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/16 13:38:25 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	error(char **buff, char **line, int fd)
{
	*buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!*buff || !line || BUFFER_SIZE <= 0 || fd < 0 || fd > 256)
	{
		if (*buff)
			free(*buff);
		return (-1);
	}
	return (0);
}

static char	*new_line(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strchr(str, '\n'));
}

static int	split_line(char **line, char **content)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while ((*content)[i] && (*content)[i] != '\n')
		++i;
	if ((*content)[i] == '\0')
	{
		(*line) = ft_strdup(*content);
		free(*content);
		(*content) = NULL;
		return (0);
	}
	tmp = (*content);
	(*line) = ft_strndup(tmp, i);
	(*content) = ft_strdup(tmp + i + 1);
	free(tmp);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*content[256];
	char		*buff;
	char		*tmp;
	int			rlen;

	rlen = 1;
	if (error(&buff, line, fd))
		return (-1);
	while (!new_line(content[fd]) && rlen > 0)
	{
		rlen = read(fd, buff, BUFFER_SIZE);
		tmp = content[fd];
		if (rlen != -1)
		{
			buff[rlen] = 0;
			content[fd] = ft_strjoin(content[fd], buff);
		}
		free(tmp);
	}
	free(buff);
	if (rlen < 0)
		return (-1);
	return (split_line(line, &content[fd]));
}
