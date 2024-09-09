/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:11:29 by pokpalae          #+#    #+#             */
/*   Updated: 2023/11/30 19:52:04 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	long	hold;

	hold = n;
	if (hold < 0)
	{
		ft_putchar_fd('-', fd);
		hold *= -1;
	}
	if (hold >= 10)
	{
		ft_putnbr_fd(hold / 10, fd);
		ft_putchar_fd(hold % 10 + '0', fd);
	}
	else
		ft_putchar_fd(hold + '0', fd);
}
