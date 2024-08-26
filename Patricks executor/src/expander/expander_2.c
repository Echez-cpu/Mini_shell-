/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:20:18 by pokpalae          #+#    #+#             */
/*   Updated: 2024/08/26 15:28:04 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

char	*expand_variable(t_tools *tools, char *str, int dollar_pos)
{
	char	*tmp;

	tmp = NULL;
	if (dollar_pos >= 1 && dollar_pos != 0
		&& str[dollar_pos] != '\0')
	{
		tmp = detect_dollar_sign(tools, str);
		if (tmp != NULL)
		{
			free(str);
			str = tmp;
		}
	}
	return (str);
}



static char	*handle_quote(char *str)
{
	char	*new_str;

	new_str = delete_quotes(str, '\"');
	if (new_str)
	{
		str = new_str;
		new_str = delete_quotes(str, '\'');
		if (new_str)
			str = new_str;
	}
	return (str);
}

char	**expander(t_tools *tools, char **str)
{
	int		i;
	int		dollar_pos;

	i = 0;
	while (str[i] != NULL)
	{
		dollar_pos = dollar_sign(str[i]);
		str[i] = expand_variable(tools, str[i], dollar_pos);
		if (ft_strncmp(str[0], "export", ft_strlen(str[0]) - 1) != 0)
			str[i] = handle_quote(str[i]);
		i++;
	}
	return (str);
}
