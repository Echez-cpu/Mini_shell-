#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	echo(char **args)
{
	int	i;
	int	j;
	int	n;

	i = 1;
	n = 1;
	if (args[1] == NULL)
		return ((write(1, "\n", 1) < 0));
	while ((strncmp(args[i], "-n", 2) == 0))
		n = (0 * i++);
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			ft_putchar_fd(args[i][j], 1);
			j++;
		}
		i++;
		if (write(1, " ", (args[i] != NULL)) < 0)
			return (-1);
	}
	return ((write(1, "\n", n) < 0));
}