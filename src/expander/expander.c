/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:29:47 by pokpalae          #+#    #+#             */
/*   Updated: 2024/08/27 12:56:31 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	loop_if_dollar_sign(t_tools *tools, char *str, char **tmp, int j)
{
	int		k;
	int		ret;
	char	*tmp2;
	char	*tmp3;

	k = 0;
	ret = 0;
	while (tools->envp[k])
	{
		if (ft_strncmp(str + j + 1, tools->envp[k], equal_sign(tools->envp[k])
				- 1) == 0 && after_dol_lenght(str, j)
			- j == (int)equal_sign(tools->envp[k]))
		{
			tmp2 = ft_strdup(tools->envp[k] + equal_sign(tools->envp[k]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			ret = equal_sign(tools->envp[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = after_dol_lenght(str, j) - j;
	return (ret);
}

char	*expander_str(t_tools *tools, char *str)
{
	char	*tmp;
	int		dollar_pos;

	tmp = NULL;
	dollar_pos = dollar_sign(str);
	if (dollar_pos >= 2 && str[dollar_pos - 2] != '\'' && dollar_pos != 0
		&& str[dollar_pos] != '\0')
	{
		tmp = detect_dollar_sign(tools, str);
		if (tmp != NULL)
		{
			free(str);
			str = tmp;
		}
	}
	str = delete_quotes(str, '\"');
	str = delete_quotes(str, '\'');
	return (str);
}
