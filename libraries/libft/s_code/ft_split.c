/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:25:13 by pokpalae          #+#    #+#             */
/*   Updated: 2023/11/30 19:52:18 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**free_array(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
	return ((void *)0);
}

static int	no_substrings(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] != '\0' && str[i] != c)
			{
				i++;
			}
		}
	}
	return (count);
}

static char	*put_string(char *word, char const *s, int i, int word_len)
{
	int	j;

	j = 0;
	while (word_len > 0)
	{
		word[j] = s[i - word_len];
		j++;
		word_len--;
	}
	word[j] = '\0';
	return (word);
}

static char	**split_strings(char const *s, char c, char **s2, int no_of_words)
{
	int	i;
	int	word;
	int	word_len;

	i = 0;
	word = 0;
	word_len = 0;
	while (word < no_of_words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			word_len++;
		}
		s2[word] = (char *)malloc((word_len + 1) * sizeof(char));
		if (!s2[word])
			return (free_array(s2, word));
		put_string(s2[word], s, i, word_len);
		word_len = 0;
		word++;
	}
	s2[word] = ((void *)0);
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char			**s2;
	unsigned int	no_of_words;

	if (!s)
		return ((void *)0);
	no_of_words = no_substrings(s, c);
	s2 = (char **)malloc((no_of_words + 1) * sizeof(char *));
	if (!s2)
		return ((void *)0);
	s2 = split_strings(s, c, s2, no_of_words);
	return (s2);
}
