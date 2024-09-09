/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:33:59 by pokpalae          #+#    #+#             */
/*   Updated: 2023/12/12 17:17:53 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_put_string(char *str)
{
	int	i;

	i = 0;
	if (str == ((void *)0))
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_process(va_list ap, const char format)
{
	int	no_char_printd;

	no_char_printd = 0;
	if (format == 'c')
		no_char_printd += ft_putchar(va_arg(ap, int));
	else if (format == 's')
		no_char_printd += ft_put_string(va_arg(ap, char *));
	else if (format == 'p')
		no_char_printd += ft_putptr(va_arg(ap, uintptr_t));
	else if (format == 'd' || format == 'i')
		no_char_printd += ft_putnbr(va_arg(ap, int));
	else if (format == 'u')
		no_char_printd += ft_putunsigned(va_arg(ap, unsigned int));
	else if (format == 'x' || format == 'X')
		no_char_printd += ft_show_hex(va_arg(ap, unsigned int), format);
	else if (format == '%')
		no_char_printd += ft_putchar('%');
	return (no_char_printd);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		no_char_printd;
	va_list	ap;

	i = 0;
	no_char_printd = 0;
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			no_char_printd += ft_process(ap, format[i + 1]);
			i++;
		}
		else
			no_char_printd += ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (no_char_printd);
}
