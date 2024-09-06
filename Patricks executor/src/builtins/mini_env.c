/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:24:14 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/06 23:07:22 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_var_in_envp(char **envp, char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			if (envp[i][ft_strlen(var)] == '=')
				return (i + 1);
		i++;
	}
	return (0);
}

int	get_envp_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**add_var_envp(char **envp, char *var, char *val)
{
	int		i;
	char	**new_envp;
	char	*tmp;

	new_envp = (char **)malloc((get_envp_size(envp) + 2) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = envp[i];
		i++;
	}
	tmp = ft_strjoin(var, "=");
	new_envp[i] = gnl_strjoin(tmp, val);
	i++;
	new_envp[i] = NULL;
	free(envp);
	return (new_envp);
}

int	set_val_envp(char **envp, char *var, char *val)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			if (envp[i][ft_strlen(var)] == '=')
			{
				free(envp[i]);
				envp[i] = malloc(ft_strlen(var) + ft_strlen(val) + 2);
				envp[i] = ft_strjoin(var, "=");
				envp[i] = gnl_strjoin(envp[i], val);
			}
		}
		i++;
	}
	return (0);
}

int	mini_env(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int	i;

	(void)simple_cmd;
	i = 0;
	while (tools->envp[i])
	{
		ft_putendl_fd(tools->envp[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
