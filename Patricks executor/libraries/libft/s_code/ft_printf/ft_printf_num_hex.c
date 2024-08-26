/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:47:42 by pokpalae          #+#    #+#             */
/*   Updated: 2023/12/11 23:21:04 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_hex_helper(char buffer[], int *index, int digit,
		const char format)
{
	if (digit <= 9)
		buffer[(*index)++] = digit + '0';
	else
	{
		if (format == 'x')
			buffer[(*index)++] = digit - 10 + 'a';
		if (format == 'X')
			buffer[(*index)++] = digit - 10 + 'A';
	}
}

void	ft_put_hex(unsigned int num, const char format)
{
	char	buffer[100];
	int		index;
	int		quotient;
	int		remainder;

	index = 0;
	while (num >= 16)
	{
		quotient = num / 16;
		remainder = num % 16;
		ft_put_hex_helper(buffer, &index, remainder, format);
		num = quotient;
	}
	ft_put_hex_helper(buffer, &index, num, format);
	while (index > 0)
	{
		ft_putchar(buffer[--index]);
	}
}

int	ft_show_hex(unsigned int num, const char format)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
	{
		ft_put_hex(num, format);
	}
	return (hex_length(num));
}

int	hex_length(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}
