/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned_int.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:49:33 by pokpalae          #+#    #+#             */
/*   Updated: 2023/12/13 14:01:03 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_length_unsignd(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*ft_usignd_itoa(unsigned int nb)
{
	char	*str;
	int		len;

	len = ft_length_unsignd(nb);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return ((void *)0);
	str[len] = '\0';
	while (nb != 0)
	{
		str[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	return (str);
}

int	ft_putunsigned(unsigned int nb)
{
	int		no_char_printd;
	char	*str;

	no_char_printd = 0;
	if (nb == 0)
		no_char_printd += write(1, "0", 1);
	else
	{
		str = ft_usignd_itoa(nb);
		no_char_printd += ft_put_string(str);
		free(str);
	}
	return (no_char_printd);
}
