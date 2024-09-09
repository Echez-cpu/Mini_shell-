/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:17:28 by pokpalae          #+#    #+#             */
/*   Updated: 2023/12/03 21:54:38 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;
	t_list	*content_result;

	if (!f || !lst)
		return (((void *)0));
	new_list = NULL;
	while (lst != ((void *)0))
	{
		content_result = f(lst->content);
		node = ft_lstnew(content_result);
		if (!node)
		{
			del(content_result);
			ft_lstclear(&new_list, del);
			return ((void *)0);
		}
		ft_lstadd_back(&new_list, node);
		lst = lst->next;
	}
	lst = (NULL);
	return (new_list);
}
