/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:33:20 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/06 21:44:35 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	question_mark(char **tmp)
{
	free(*tmp);
	*tmp = ft_itoa(gs_error_num(-1));
	return (ft_strlen(*tmp) + 1);
}
