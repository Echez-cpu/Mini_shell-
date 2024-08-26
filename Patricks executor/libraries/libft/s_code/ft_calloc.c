/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:04:23 by pokpalae          #+#    #+#             */
/*   Updated: 2023/12/01 19:36:44 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	tot_size;
	void	*ptr;
	size_t	i;

	if (size != 0 && count != 0 && count > SIZE_MAX / size)
	{
		return ((void *)0);
	}
	tot_size = count * size;
	ptr = malloc(tot_size);
	if (ptr == ((void *)0))
	{
		return ((void *)0);
	}
	i = 0;
	while (i < tot_size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
