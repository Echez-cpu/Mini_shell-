/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:37:34 by pokpalae          #+#    #+#             */
/*   Updated: 2023/11/30 19:51:05 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	digit_count(int n);
static void	fill_digits(char *result, int n, int count);
static void	fill_digits2(char *result, long long n, int count);

static void	fill_digits2(char *result, long long n, int count)
{
	int	i;

	result[0] = '-';
	n = -n;
	i = count;
	while (n != 0)
	{
		i--;
		result[i] = '0' + n % 10;
		n /= 10;
	}
}

static int	digit_count(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		count = 1;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	fill_digits(char *result, int n, int count)
{
	int	i;

	i = count - 1;
	if (n == 0)
		result[i--] = '0';
	while (n != 0)
	{
		result[i] = '0' + n % 10;
		n /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	int		count;
	char	*result;

	count = digit_count(n);
	result = (char *)malloc((count + 1) * sizeof(char));
	if (!result)
		return ((void *)0);
	if (n < 0)
	{
		fill_digits2(result, n, count);
	}
	else
		fill_digits(result, n, count);
	result[count] = '\0';
	return (result);
}
