/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:46:21 by pokpalae          #+#    #+#             */
/*   Updated: 2023/11/30 19:52:37 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	len;
	char	*dub;
	char	*dup_ptr;

	len = 0;
	while (s1[len] != '\0')
		len++;
	dub = (char *)malloc((len + 1) * sizeof(char));
	dup_ptr = dub;
	if (dub == ((void *)0))
		return ((void *)0);
	i = 0;
	while (s1[i] != '\0')
	{
		*dup_ptr = s1[i];
		i++;
		dup_ptr++;
	}
	*dup_ptr = '\0';
	return (dub);
}
