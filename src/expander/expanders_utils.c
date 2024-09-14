/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:29:59 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/14 15:49:29 by tlaukat          ###   ########.fr       */
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

char	*delete_quotes(char *str, char c)
{
	int	i;
	int	quote_lock;

	if (c == '"')
		return (str);
	i = 0;
	quote_lock = 0;
	while (str[i])
	{
		if (str[i] == '\"' && quote_lock != 1)
		{
			ft_strlcpy(&str[i], &str[i + 1], strlen(str) - i);
			quote_lock = 2 - quote_lock;
		}
		else if (str[i] == '\'' && quote_lock != 2)
		{
			ft_strlcpy(&str[i], &str[i + 1], strlen(str) - i);
			quote_lock = 1 - quote_lock;
		}
		else
			i++;
	}
	return (str);
}
