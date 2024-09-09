/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:24:47 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/09 01:16:35 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_var_in_arr(char **arr, char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	while (arr[i])
	{
		if (ft_strncmp(arr[i], var, ft_strlen(var)) == 0)
			if (arr[i][ft_strlen(var)] == '=' || arr[i][ft_strlen(var)] == 0)
				return (i + 1);
		i++;
	}
	return (0);
}

char	**del_var_unset(char **arr, char *var)
{
	int		i;
	int		pos;
	char	**new_arr;
	char	*tmp;

	i = -1;
	tmp = ft_strdup(var);
	pos = is_var_in_arr(arr, tmp) - 1;
	free(tmp);
	if (pos == -1)
		return (NULL);
	new_arr = (char **)malloc((get_envp_size(arr)) * sizeof(char *));
	while (++i < pos)
		new_arr[i] = arr[i];
	while (i < get_envp_size(arr) - 1)
	{
		new_arr[i] = arr[i + 1];
		i++;
	}
	free(arr[pos]);
	free(arr);
	new_arr[i] = NULL;
	return (new_arr);
}

int	unset_error(t_simple_cmds *simple_cmd)
{
	int	i;

	i = 0;
	if (!simple_cmd->str[1])
	{
		ft_putendl_fd("minishell: unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (simple_cmd->str[1][i])
	{
		if (simple_cmd->str[1][i++] == '/')
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(simple_cmd->str[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	if (equal_sign(simple_cmd->str[1]) != 0)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	mini_unset(t_tools *tools, t_simple_cmds *simple_cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	if (unset_error(simple_cmd) == 1)
		return (EXIT_FAILURE);
	while (simple_cmd->str[++i])
	{
		tmp = del_var_unset(tools->envp, simple_cmd->str[i]);
		if (tmp != NULL)
			tools->envp = tmp;
		tmp = del_var_unset(tools->export, simple_cmd->str[i]);
		if (tmp != NULL)
			tools->export = tmp;
	}
	return (EXIT_SUCCESS);
}
