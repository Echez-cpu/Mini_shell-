/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:53:09 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/06 21:41:40 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_in_cmd = 0;

int	gs_error_num(int val)
{
	static int	g_error_num;

	if (!g_error_num)
		g_error_num = 0;
	if (val == -1)
		return (g_error_num);
	g_error_num = val;
	return (0);
}

int	get_in_cmd(void)
{
	return (g_in_cmd);
}

void	set_in_cmd(int value)
{
	g_in_cmd = value;
}
