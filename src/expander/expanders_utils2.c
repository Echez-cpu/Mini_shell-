/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:33:20 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/10 16:19:04 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	question_mark(char **tmp)
{
	char	*nmb;
	int		size;

	nmb = ft_itoa(gs_error_num(-1));
	*tmp = gnl_strjoin(*tmp, nmb);
	size = ft_strlen(nmb);
	free(nmb);
	return (size + 1);
}
