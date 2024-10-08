/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:22:28 by pokpalae          #+#    #+#             */
/*   Updated: 2024/08/27 12:44:02 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	(*builtin_arr(char *str))(t_tools *tools, t_simple_cmds *simple_cmd)
{
	static void	*builtins[7][2] = {{"echo", mini_echo}, {"cd", mini_cd}, {"pwd",
		mini_pwd}, {"export", mini_export}, {"unset", mini_unset}, {"env",
		mini_env}, {"exit", mini_exit}};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (str)
		{
			if (!ft_strncmp(builtins[i][0], str, ft_strlen((builtins[i][0]))))
			{
				if (ft_strlen(builtins[i][0]) == ft_strlen(str))
					return (builtins[i][1]);
			}
		}
		i++;
	}
	return (NULL);
}
