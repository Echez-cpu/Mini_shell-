/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:43:42 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/10 17:53:52 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char		*join_split_str(char **split_str, char *new_str);
char		**resplit_str(char **double_arr);

static void	execute_command(char **cmd_str, t_tools *tools)
{
	int		i;
	char	*mycmd;

	i = 0;
	if (!access(cmd_str[0], F_OK))
		execve(cmd_str[0], cmd_str, tools->envp);
	while (tools->paths[i])
	{
		mycmd = ft_strjoin(tools->paths[i], cmd_str[0]);
		if (!access(mycmd, F_OK))
			execve(mycmd, cmd_str, tools->envp);
		free(mycmd);
		i++;
	}
	cmd_not_found(cmd_str[0]);
	exit(127);
}

static int	handle_exit_status(int status)
{
	int	sig;
	int	exit_status;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			gs_error_num(130);
			return (130);
		}
	}
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		gs_error_num(exit_status);
		return (exit_status);
	}
	return (1);
}

static void	find_and_exec_command(t_simple_cmds *cmd, t_tools *tools)
{
	cmd->str = resplit_str(cmd->str);
	execute_command(cmd->str, tools);
}

int	find_cmd(t_simple_cmds *cmd, t_tools *tools)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		find_and_exec_command(cmd, tools);
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (handle_exit_status(status));
	}
	else
	{
		perror("fork");
		return (1);
	}
	return (1);
}
