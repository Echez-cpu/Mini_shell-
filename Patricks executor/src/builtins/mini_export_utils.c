/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:51:58 by tlaukat           #+#    #+#             */
/*   Updated: 2024/09/06 19:52:03 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		show_exported_variables(char **export);

char	*get_export_var(char *export_line)
{
	int		i;
	char	*var;

	i = 0;
	while (export_line[i] != '=' && export_line[i])
		i++;
	var = ft_substr(export_line, 0, i);
	if (!var)
	{
		perror("ft_substr: get_export_var");
		exit(-1);
	}
	return (var);
}

char	*get_export_val(char *export_line)
{
	int		i;
	char	*val;

	i = 0;
	while (export_line[i] != '=' && export_line[i])
		i++;
	if (export_line[i] && ft_strlen(export_line + i) > 3)
	{
		i += 2;
		val = ft_substr(export_line, i, ft_strlen(export_line) - i - 1);
		if (!val)
		{
			perror("ft_substr: get_export_val");
			exit(-1);
		}
	}
	else
		val = NULL;
	return (val);
}

// 0: AAA, 1: BBB, 2:DDD <- CCC, pos = 2
char	**add_new_export_p(char **export, int pos)
{
	int		i;
	char	**tmp;

	if (pos == -1)
		return (export);
	tmp = (char **)malloc(sizeof(char *) * (get_envp_size(export) + 2));
	if (!tmp)
	{
		perror("malloc: add_new_export_p");
		exit(-1);
	}
	i = -1;
	while (++i < pos)
		tmp[i] = export[i];
	tmp[pos] = NULL;
	i--;
	while (export[++i])
		tmp[i + 1] = export[i];
	tmp[i + 1] = NULL;
	free(export);
	return (tmp);
}

char	**add_var_export_2(char **export, char *var, char *val, int i)
{
	export[i] = ft_strdup(var);
	if (val)
	{
		if (export[i])
			export[i] = gnl_strjoin(export[i], "=\"");
		if (export[i])
			export[i] = gnl_strjoin(export[i], val);
		if (export[i])
			export[i] = gnl_strjoin(export[i], "\"");
	}
	if (!export[i])
	{
		perror("malloc: add_new_export_p");
		exit(-1);
	}
	return (export);
}

char	**add_var_export(char **export, char *var, char *val)
{
	int		i;
	int		b;
	char	*export_line;

	i = is_var_in_export(export, var) - 1;
	b = 0;
	if (i == -1)
	{
		while (export[++i] && !b)
		{
			export_line = get_export_var(export[i]);
			if (ft_strncmp(export_line, var, ft_strlen(var) + 1) >= 0)
				b = -1 - i--;
			free(export_line);
		}
		export = add_new_export_p(export, i);
	}
	else
	{
		export_line = ft_strchr(export[i], '=');
		free(export[i]);
		if (!export_line)
			return (export[i] = ft_strdup(var), export);
	}
	return (add_var_export_2(export, var, val, i));
}
