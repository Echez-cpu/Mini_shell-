/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:53:09 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/09 17:46:22 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	gs_in_cmd(int val)
{
	static int	g_in_cmd;

	if (!g_in_cmd)
		g_in_cmd = 0;
	if (val == -1)
		return (g_in_cmd);
	g_in_cmd = val;
	return (0);
}
