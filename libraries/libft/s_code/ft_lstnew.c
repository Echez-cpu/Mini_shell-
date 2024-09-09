/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:32:29 by pokpalae          #+#    #+#             */
/*   Updated: 2023/12/02 19:22:32 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_nd;

	new_nd = (t_list *)malloc(sizeof(t_list));
	if (!new_nd)
		return ((void *)0);
	new_nd->content = content;
	new_nd->next = ((void *)0);
	return (new_nd);
}
