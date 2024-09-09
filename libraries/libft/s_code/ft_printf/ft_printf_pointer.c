/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:21:58 by pokpalae          #+#    #+#             */
/*   Updated: 2023/12/12 18:58:17 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	len_pointer(uintptr_t nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

void	ft_put_pointer(uintptr_t nb)
{
	char	buffer[100];
	int		index;
	int		digit;

	index = 0;
	while (nb >= 16)
	{
		digit = nb % 16;
		if (digit <= 9)
			buffer[index++] = digit + '0';
		else
			buffer[index++] = digit - 10 + 'a';
		nb /= 16;
	}
	if (nb <= 9)
		buffer[index++] = nb + '0';
	else
		buffer[index++] = nb - 10 + 'a';
	while (index > 0)
	{
		ft_putchar(buffer[--index]);
	}
}

int	ft_putptr(uintptr_t ptr)
{
	int	no_char_printd;

	no_char_printd = 0;
	no_char_printd += write(1, "0x", 2);
	if (ptr == 0)
		no_char_printd += write(1, "0", 1);
	else
	{
		ft_put_pointer(ptr);
		no_char_printd += len_pointer(ptr);
	}
	return (no_char_printd);
}
