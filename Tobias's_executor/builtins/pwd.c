#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	pwd(char **args)
{
	char	*path;

	if (args[1] != NULL)
		return (printf("pwd: too many arguments\n"), 1);
	path = getcwd(NULL, 0);
	if (path == NULL)
		return (perror("pwd"), -1);
	if (write(1, path, strlen(path)) < 0)
		return (-1);
	free(path);
	return ((write(1, "\n", 1) < 0));
}