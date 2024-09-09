/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 01:39:51 by tlaukat           #+#    #+#             */
/*   Updated: 2024/09/09 01:39:54 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_var_in_export(char **export, char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	while (export[i])
	{
		tmp = get_export_var(export[i]);
		if (ft_strncmp(tmp, var, ft_strlen(var) + 1) == 0)
			return (free(tmp), i + 1);
		free(tmp);
		i++;
	}
	return (0);
}

int	show_exported_variables(char **export)
{
	int	i;

	i = 0;
	while (export[i])
		printf("declare -x %s\n", export[i++]);
	return (0);
}
