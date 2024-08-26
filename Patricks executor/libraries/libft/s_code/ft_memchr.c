/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:40:10 by pokpalae          #+#    #+#             */
/*   Updated: 2023/11/30 19:51:14 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;

	ptr = s;
	while (n > 0 && *ptr != (unsigned char)c)
	{
		ptr++;
		n--;
	}
	if (n > 0)
	{
		return ((void *)ptr);
	}
	else
	{
		return ((void *)0);
	}
}
