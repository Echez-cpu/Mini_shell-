/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal-handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:53:40 by tlaukat           #+#    #+#             */
/*   Updated: 2024/07/10 19:58:13 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	specify_for_kill(int pid)
{
	struct sigaction	new_action;

	new_action.sa_handler = kill(pid);
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	sigaction(SIGINT, &new_action, NULL);
	sigaction(SIGQUIT, &new_action, NULL);
	// sigaction(SIGINT, &new_action, NULL);
}

void	process_loop(void)
{
	while (1)
		;
}

test_process()
{
	pid_t	pid;

	pid = fork();
	if (pid != 0)
	{
		specify_for_kill(pid);
		process_loop;
	}
}

void	handle_signal(int signal)
{
	if (signal == 2)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(void)
{
	struct sigaction new_action, old_action;
	new_action.sa_handler = handle_signal;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	char *checker;
	sigaction(SIGINT, &new_action, NULL);
	// signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	checker = readline("MINISHELL>> ");
	while (checker != NULL)
	{
		write(0, checker, strlen(checker));
		write(0, "\n", 1);
		if (strncmp(checker, "exit\0", 5) == 0)
			return (0);
		if (strncmp(checker, "process\0", 8) == 0)
			test_process();
		free(checker);
		checker = readline("MINISHELL>> ");
	}
	write(0, "exit\n", 5);
	return (130);
}