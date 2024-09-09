/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:35:33 by pokpalae          #+#    #+#             */
/*   Updated: 2024/03/28 15:35:38 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_put_hex(unsigned int num, const char format);
void	ft_put_pointer(uintptr_t nb);
int		hex_length(unsigned int num);
int		len_pointer(uintptr_t nb);
int		ft_length_unsignd(unsigned int nb);
int		ft_putchar(int c);
int		ft_put_string(char *str);
int		ft_putnbr(int n);
int		ft_show_hex(unsigned int num, const char format);
int		ft_putptr(uintptr_t ptr);
int		ft_putunsigned(unsigned int nb);
int		ft_process(va_list ap, const char format);
int		ft_printf(const char *format, ...);
char	*ft_usignd_itoa(unsigned int nb);
void	ft_put_hex_helper(char buffer[], int *index, int digit,
			const char format);
#endif