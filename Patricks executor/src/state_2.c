/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:50:42 by pokpalae          #+#    #+#             */
/*   Updated: 2024/08/24 20:52:02 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_in_heredoc = 0;
static int	g_stop_heredoc = 0;

int	get_in_heredoc(void)
{
	return (g_in_heredoc);
}

int	get_stop_heredoc(void)
{
	return (g_stop_heredoc);
}

void	set_in_heredoc(int value)
{
	g_in_heredoc = value;
}

void	set_stop_heredoc(int value)
{
	g_stop_heredoc = value;
}
