/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:36:22 by tlaukat           #+#    #+#             */
/*   Updated: 2024/02/14 18:44:34 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_multiple(char *s1, char *s2, char **res)
{
	int	i;

	i = 0;
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (res)
	{
		while (res[i])
		{
			free(res[i]);
			i++;
		}
		free(res);
		res = NULL;
	}
	return (NULL);
}

char	*read_file(int fd, char *res)
{
	int		buf_res;
	char	*buffer;

	if (!res)
		res = gnl_calloc(1, 1);
	buffer = gnl_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer || !res)
		return (free_multiple(res, buffer, NULL));
	buf_res = 1;
	while (buf_res > 0 && !gnl_strchr(buffer, '\n'))
	{
		buf_res = read(fd, buffer, BUFFER_SIZE);
		if (buf_res == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[buf_res] = '\0';
		res = gnl_strjoin(res, buffer);
		if (!res)
			return (free_multiple(res, buffer, NULL));
	}
	free(buffer);
	return (res);
}

char	*gnl_get_overflow(char *res)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	while (res[i] != '\n' && res[i] != '\0')
		i++;
	if (!res[i])
		return (free_multiple(res, NULL, NULL));
	buffer = gnl_calloc(gnl_strlen(res) - i + 1, 1);
	if (!buffer)
		return (free_multiple(res, buffer, NULL));
	i++;
	j = 0;
	while (res[i])
	{
		buffer[j++] = res[i++];
	}
	free(res);
	return (buffer);
}

char	*gnl_get_line(char *res)
{
	int		i;
	char	*buffer;

	i = 0;
	if (!res[i])
		return (NULL);
	while (res[i] != '\n' && res[i] != '\0')
		i++;
	buffer = gnl_calloc(i + 2, 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (res[i] != '\n' && res[i] != '\0')
	{
		buffer[i] = res[i];
		i++;
	}
	if (res[i] && res[i] == '\n')
		buffer[i++] = '\n';
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*res[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || MAX_FD < fd || read(fd, 0, 0) < 0)
	{
		if (res[fd])
			free(res[fd]);
		res[fd] = NULL;
		return (NULL);
	}
	res[fd] = read_file(fd, res[fd]);
	if (!res[fd])
		return (NULL);
	line = gnl_get_line(res[fd]);
	res[fd] = gnl_get_overflow(res[fd]);
	return (line);
}
