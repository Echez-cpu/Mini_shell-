#include "../libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_tools
{

	char    **envp;
	char    **export;
}	t_tools;

//export functions
char *get_export_var(char *export_line);
char *get_export_val(char *export_line);
int is_var_in_export(char **export, char *var);
char **add_var_export(char **export, char *var, char *val);

//envp functions
int is_var_in_envp(char **envp, char *var);
int get_envp_size(char **envp);
char **add_var_envp(char **envp, char *var, char *val);
int set_val_envp(char **envp, char *var, char *val);

