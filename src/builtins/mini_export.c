/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:24:26 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/09 01:48:11 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "state.h"

int	export_variable(char *var, char *val, t_tools *tools)
{
	if (!is_var_in_export(tools->export, var) || val)
		tools->export = add_var_export(tools->export, var, val);
	else
		return (EXIT_SUCCESS);
	if (!val)
		return (EXIT_SUCCESS);
	if (!is_var_in_envp(tools->envp, var))
		return (tools->envp = add_var_envp(tools->envp, var, val), 0);
	return (set_val_envp(tools->envp, var, val));
}

// add Checker: [a-z,A-Z,_][0-9,a-z,A-Z,_]
//$_ ignorieren, $__ ist ok, $02 ist nicht ok, $1 auch nicht,
//	andere Zeichen sind auch nicht ok

int	var_is_valid(char *var, char *arg)
{
	int	i;
	int	v;

	i = 0;
	v = 0;
	if (var[0] == '_')
	{
		if (var[1] == 0)
			v = 2;
	}
	else if (!(ft_isalpha(var[0])))
		v = 1;
	while (var[++i] && v == 0)
		if (!(var[i] == '_' || ft_isalnum(var[i])))
			v = 1;
	if (v == 1)
		printf("export: `%s': not a valid identifier\n", arg);
	return (v);
}

int	export(t_tools *tools, char **args)
{
	int		ret;
	char	*var;
	char	*val;

	if (args[1] == NULL)
		return (show_exported_variables(tools->export));
	while (++args && args[0])
	{
		var = get_export_var(args[0]);
		val = get_export_val(args[0]);
		if (var_is_valid(var, args[0]) == 0)
			ret = export_variable(var, val, tools);
		else
			ret = EXIT_FAILURE;
		if (val)
			free(val);
		free(var);
	}
	return (ret);
}

int	mini_export(t_tools *tools, t_simple_cmds *simple_cmd)
{
	char	**args;
	int		ret;

	args = ft_arrdup(simple_cmd->str);
	ret = export(tools, args);
	free_arr(args);
	return (ret);
}
