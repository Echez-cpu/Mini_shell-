#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libft.h"

char *replace(char *str, char *var, int start, int length) 
{
	if(var)
    {
		size_t len = strlen(str) - length + strlen(var) + 1; 
    	char *new = (char*)malloc(len);
    	if (new == NULL) 
        	return (perror("parsing: replace"), NULL);
    	ft_strlcpy(new, str, start + 1); 
    	ft_strlcpy(new + start, var, len - start);
    	ft_strlcpy(new + start + strlen(var), str + start + length, len - start - strlen(var));
    	free(str);
    	free(var);
	}
		size_t len = strlen(str) - length + 1; 
    	char *new = (char*)malloc(len);
    	if (new == NULL) 
        	return (perror("parsing: replace"), NULL);
    	ft_strlcpy(new, str, start + 1); 
    	ft_strlcpy(new + start, str + start + length, len - start);
    	free(str);
    return new;
}

int	main(int argc, char **argv)
{
	if(argc!=5)
		return;
	char *str=replace(ft_strdup(argv[1]), NULL, ft_atoi(argv[3]), ft_atoi(argv[4]));
	printf("%s\n", str);
	return(0);
}