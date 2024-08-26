/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:33:20 by pokpalae          #+#    #+#             */
/*   Updated: 2024/08/24 20:16:22 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	question_mark(char **tmp)
{
	free(*tmp);
	*tmp = ft_itoa(get_error_num());
	return (ft_strlen(*tmp) + 1);
}
