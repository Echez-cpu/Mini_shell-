/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:33:20 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/12 11:25:16 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	question_mark(char **tmp)
{
	char	*nmb;
	int		size;

	nmb = ft_itoa(gs_error_num(-1));
	*tmp = gnl_strjoin(*tmp, nmb);
	size = ft_strlen(nmb);
	free(nmb);
	return (size + 1);
}

size_t	quotes_lenght(char *str)
{
	int		i;
	size_t	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ret++;
		}
		i++;
	}
	return (ret);
}

char	*delete_quotes_2(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}
