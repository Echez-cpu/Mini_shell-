/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:24:47 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/06 23:12:51 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**del_var_unset(char **arr, char *var)
{
	int		i;
	int		pos;
	char	**new_arr;
	char	*tmp;

	i = -1;
	write(1, "here1\n", 6);
	tmp = ft_strjoin(var, "=");
	pos = is_var_in_envp(arr, tmp) - 1;
	if (pos == -1)
		return (NULL);
	write(1, "here2\n", 6);
	new_arr = (char **)malloc((get_envp_size(arr)) * sizeof(char *));
	while (++i < pos)
		new_arr[i] = arr[i];
	while (i < get_envp_size(arr) - 1)
	{
		new_arr[i] = arr[i + 1];
		i++;
	}
	write(1, "here3\n", 6);
	free(arr[pos]);
	new_arr[i] = NULL;
	free(tmp);
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
	char	**args_env;
	char	**args_exp;
	int		i;

	i = 0;
	if (unset_error(simple_cmd) == 1)
		return (EXIT_FAILURE);
	args_env = ft_arrdup(tools->envp);
	args_exp = ft_arrdup(tools->export);
	free(tools->envp);
	free(tools->export);
	while (simple_cmd->str[++i])
	{
		tmp = del_var_unset(args_env, simple_cmd->str[i]);
		free_arr(args_env);
		if (tmp != NULL)
			args_env = tmp;
		tmp = del_var_unset(args_exp, simple_cmd->str[i]);
		free_arr(args_exp);
		if (tmp != NULL)
			args_exp = tmp;
	}
	tools->envp = args_env;
	tools->export = args_exp;
	free_arr(args_env);
	free_arr(args_exp);
	return (EXIT_SUCCESS);
}
