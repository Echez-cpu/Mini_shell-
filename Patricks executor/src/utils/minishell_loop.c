/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:09:43 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/06 22:24:02 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_loop(t_tools *tools);

int	add_env_to_export(t_tools *tools)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tools->envp[i])
	{
		tmp = ft_strdup(tools->envp[i++]);
		tools->export = add_var_export(tools->export, tmp, NULL);
		free(tmp);
	}
	return (0);
}

int	implement_tools(t_tools *tools)
{
	tools->simple_cmds = NULL;
	tools->lexer_list = NULL;
	tools->reset = false;
	tools->pid = NULL;
	tools->heredoc = false;
	gs_stop_heredoc(0);
	set_in_cmd(0);
	gs_in_heredoc(0);
	parse_envp(tools);
	init_signals();
	return (1);
}

int	reset_tools(t_tools *tools)
{
	ft_simple_cmdsclear(&tools->simple_cmds);
	free(tools->args);
	if (tools->pid)
		free(tools->pid);
	free_arr(tools->paths);
	implement_tools(tools);
	tools->reset = true;
	minishell_loop(tools);
	return (1);
}

int	prepare_executor(t_tools *tools)
{
	signal(SIGQUIT, sigquit_handler);
	set_in_cmd(1);
	if (tools->pipes == 0)
		single_cmd(tools->simple_cmds, tools);
	else
	{
		tools->pid = ft_calloc(sizeof(int), tools->pipes + 2);
		if (!tools->pid)
			return (ft_error(1, tools));
		executor(tools);
	}
	set_in_cmd(0);
	return (EXIT_SUCCESS);
}

int	minishell_loop(t_tools *tools)
{
	char	*tmp;

	tools->args = readline(READLINE_MSG);
	tmp = ft_strtrim(tools->args, " ");
	free(tools->args);
	tools->args = tmp;
	if (!tools->args)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		free_tools(tools);
		exit(EXIT_SUCCESS);
	}
	if (tools->args[0] == '\0')
		return (reset_tools(tools));
	add_history(tools->args);
	if (!count_quotes(tools->args))
		return (ft_error(2, tools));
	if (!token_reader(tools))
		return (ft_error(1, tools));
	parser(tools);
	prepare_executor(tools);
	reset_tools(tools);
	return (1);
}
