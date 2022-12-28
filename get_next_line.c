/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolemmen <lolemmen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:19:31 by jmeulema          #+#    #+#             */
/*   Updated: 2022/12/28 22:28:44 by lolemmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *stash, char *str)
{
	char	*mem;

	if (!stash)
		stash = ft_calloc(1,1);
	mem = ft_strjoin(stash, str);
	free(stash);
	return (mem);
}

static char	*ft_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	return (line);
}

static char	*ft_next(char *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || (stash[i] || !stash[i + 1]))
	{
		free(stash);
		return (NULL);
	}
	line = ft_calloc(ft_strlen(stash) - i + 1, sizeof(char));
	i++;
	j = 0;
	while (stash[i])
	{
		line[j] = stash[i];
		i++;
		j++;
	}
	line[j] = '\0';
	free(stash);
	return (line);
}

char	*ft_read_file(int fd, char *res)
{
	char	*buffer;
	int		nbyte;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	nbyte = 1;
	while (!ft_strchr(buffer, '\n') && nbyte > 0)
	{
		nbyte = read(fd, buffer, BUFFER_SIZE);
		if (nbyte == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[nbyte] = '\0';
		res = ft_free(res, buffer);
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stash = ft_read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_line(stash);
	stash = ft_next(stash);
	return (line);
}
