/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:53:09 by pokpalae          #+#    #+#             */
/*   Updated: 2024/08/27 13:36:09 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_error_num = 0;
static int	g_in_cmd = 0;

int	get_error_num(void)
{
	return (g_error_num);
}

int	get_in_cmd(void)
{
	return (g_in_cmd);
}

void	set_error_num(int value)
{
	g_error_num = value;
}

void	set_in_cmd(int value)
{
	g_in_cmd = value;
}
