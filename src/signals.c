/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:42:19 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/14 16:06:49 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "state.h"

static volatile sig_atomic_t	g_signal_received = 0;

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	sigint_handler(int sig)
{
	g_signal_received = sig;
	if (!gs_in_heredoc(-1))
		ft_putstr_fd("\n", STDERR_FILENO);
	if (gs_in_cmd(-1))
	{
		gs_stop_heredoc(1);
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	gs_error_num(130);
}

void	sigquit_handler(int sig)
{
	ft_putchar_fd('\n', STDERR_FILENO);
	gs_error_num(128 + sig);
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGTSTP, SIG_IGN);
}
