#include "builtins.h"

int is_var_in_envp(char **envp, char *var)
{
	int i;
	
	i=0;
	if(!var)
		return(0);
	while(envp[i])
	{
		if(ft_strncmp(envp[i], var, ft_strlen(var))==0)
			if(envp[i][ft_strlen(var)]=='=')
				return(1);
		i++;
	}
	return(0);

}

int get_envp_size(char **envp)
{
	int i = 0;
	while(envp[i])
		i++;
	return(i);
}

char ** add_var_envp(char **envp, char *var, char *val)
{
	int i;
	char** new_envp;

	new_envp = (char**)malloc((get_envp_size(envp) + 2) *sizeof(char*));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i]=ft_strjoin(var, "=");
	new_envp[i]=ft_strjoin(new_envp[i], val);
	i++;
	new_envp[i]=NULL;
	free(envp);
	return(new_envp);
}

int set_val_envp(char **envp, char *var, char *val)
{
	int i;
	
	i=0;
	if(!var)
		return(0);
	while(envp[i])
	{
		if(ft_strncmp(envp[i], var, ft_strlen(var))==0)
			if(envp[i][ft_strlen(var)]=='=')
				{
					free(envp[i]);
					envp[i]=malloc(ft_strlen(var)+ft_strlen(val)+2);
					envp[i]=ft_strjoin(var, "=");
					envp[i]=gnl_strjoin(envp[i], val);
				}
		i++;
	}
	return(0);
}