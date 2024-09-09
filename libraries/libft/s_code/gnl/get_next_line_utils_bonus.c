/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:36:57 by tlaukat           #+#    #+#             */
/*   Updated: 2024/02/14 18:44:35 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	gnl_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

void	*gnl_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	gnl_bzero(ptr, size * count);
	return (ptr);
}

char	*gnl_strchr(const char *s, int c)
{
	char	*res;

	res = (char *)s;
	if (c < 0)
		return (NULL);
	while (c >= 256)
		c = c - 256;
	while (*res != '\0' && *res != c)
	{
		res++;
	}
	if (*res == c)
	{
		return (res);
	}
	return (NULL);
}

char	*gnl_strjoin(char *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!ptr || !s1 || !s2)
		return (NULL);
	while (s1[j] != '\0')
	{
		ptr[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}
