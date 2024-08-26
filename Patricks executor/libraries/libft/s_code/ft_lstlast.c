/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 20:26:55 by pokpalae          #+#    #+#             */
/*   Updated: 2023/12/02 20:44:43 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == ((void *)0))
		return ((void *)0);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
