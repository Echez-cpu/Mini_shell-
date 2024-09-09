/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:50:42 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/06 21:24:56 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gs_in_heredoc(int val)
{
	static int	g_in_heredoc;

	if (!g_in_heredoc)
		g_in_heredoc = 0;
	if (val == -1)
		return (g_in_heredoc);
	g_in_heredoc = val;
	return (0);
}

int	gs_stop_heredoc(int val)
{
	static int	g_stop_heredoc;

	if (!g_stop_heredoc)
		g_stop_heredoc = 0;
	if (val == -1)
		return (g_stop_heredoc);
	g_stop_heredoc = val;
	return (0);
}
