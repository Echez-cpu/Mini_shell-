/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:49:21 by pokpalae          #+#    #+#             */
/*   Updated: 2023/12/01 17:05:39 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	backward_copy(unsigned char *destination,
				const unsigned char *source, size_t len);

static void	backward_copy(unsigned char *destination,
		const unsigned char *source, size_t len)
{
	destination += len - 1;
	source += len - 1;
	while (len > 0)
	{
		*destination = *source;
		destination--;
		source--;
		len--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*destination;
	const unsigned char	*source;

	if (dst == ((void *)0) && src == ((void *)0))
	{
		return ((void *)0);
	}
	destination = dst;
	source = src;
	if (destination < source || destination >= source + len)
	{
		while (len > 0)
		{
			*destination = *source;
			destination++;
			source++;
			len--;
		}
	}
	else
	{
		backward_copy(destination, source, len);
	}
	return (dst);
}
