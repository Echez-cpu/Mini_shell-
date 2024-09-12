/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:29:59 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/12 11:06:35 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

size_t	dollar_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*char_to_str(char c)
{
	char	*str;

	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	return (str);
}

int	after_dol_lenght(char *str, int j)
{
	int	i;

	i = j + 1;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' ' && str[i] != '\"'
		&& str[i] != '\'' && str[i] != '=' && str[i] != '-' && str[i] != ':')
		i++;
	return (i);
}

int	quote_count_line(char *line)
{
	int	n;
	int	quote_lock;

	n = 0;
	quote_lock = 0;
	while (*line)
	{
		n++;
		if (*line == 34 && quote_lock != 1)
		{
			quote_lock = 2 - quote_lock;
			n--;
		}
		if (*line == 39 && quote_lock != 2)
		{
			quote_lock = 1 - quote_lock;
			n--;
		}
		line++;
	}
	return (n);
}

char	*delete_quotes(char *line, char c)
{
	int		i;
	int		skip;
	int		quote_lock;
	char	*temp;

	if (c == '"')
		return (line);
	temp = (char *)ft_calloc(quote_count_line(line) + 1, 1);
	if (temp == NULL)
		return (NULL);
	i = 0;
	quote_lock = 0;
	while (*line)
	{
		skip = 0;
		if (*line == 34 && quote_lock != 1)
			quote_lock = 2 - quote_lock + skip++;
		if (*line == 39 && quote_lock != 2)
			quote_lock = 1 - quote_lock + skip++;
		if (!skip)
			temp[i++] = *line;
		line++;
	}
	return (temp);
}
