#include "builtins.h"

int	show_exported_variables(char **export)
{
    int i;
	
    i=0;
	while(export[i])
        printf("declare -x %s\n", export[i++]);
	return (0);
}

int	export_variable(char *var, char *val, t_tools *tools)
{
    if(!is_var_in_export(tools->export, var) || val)
	    tools->export = add_var_export(tools->export, var, val);
    else
        return 0;
	if(!is_var_in_envp(tools->envp, var))
		return(tools->envp = add_var_envp(tools->envp, var, val), 0);
	return(set_val_envp(tools->envp, var, val));
}


//add Checker: [a-z,A-Z,_][0-9,a-z,A-Z,_]   $_ ignorieren, $__ ist ok, $02 ist nicht ok, $1 auch nicht, andere Zeichen sind auch nicht ok
int var_is_valid(char *var, char *arg)
{
    int i;
    int v;

    i=0;
    v=0;
    if(var[0]=='_')
    {
        if(var[1]==0)
            v=2;
    }
    else 
        if(!(ft_isalpha(var[0])))
            v=1;
    while(var[++i] && v==0)
        if(!(var[i] =='_' || ft_isalnum(var[i])))
            v=1;
    if(v==1)
    {
        printf("%d: %s\n", i, var);
        printf("export: `%s': not a valid identifier\n", arg);
    }
    return(v);
}

int	export(char **args, t_tools *tools)
{
	int		i;
	int		j;
	char	*var;
	char	*val;

	i = 0;
	if (args[1] == NULL)
		return (show_exported_variables(tools->export));
	while (args[++i])
	{
		j = 0;
		while (args[i][j] != '=' && args[i][j])
			j++;
		var = ft_substr(args[i], 0, j);
		if(args[i][j])
			{j++;val = ft_substr(args[i], j, ft_strlen(args[i]) - j);}
		else
			val = NULL;
        if(var_is_valid(var, args[i])==0)
		    export_variable(var, val, tools);
        if(val)
		    free(val);
		free(var);
	}
    return 0;
}

int main (int argc, char** argv, char** env)
{
    t_tools *tools = malloc(sizeof(t_tools));
    int i = -1;
    char **envp;
    char **exp;

    envp = malloc(sizeof(char*) * (get_envp_size(env) + 1));
    while(env[++i])
        envp[i] = ft_strdup(env[i]);
    envp[i] = NULL;
    exp = (char**)malloc(sizeof(char*));
    exp[0]=NULL;
    tools->envp = envp;
    tools->export = exp;
    export(envp, tools);
    export_variable("OLDPWD", NULL, tools);
    export_variable("SHELL", "Minishell", tools);
    export(argv, tools);

    //show
    //printf("ENV:\n");
    //show_exported_variables(tools->envp);
    printf("EXPORT:\n");
    show_exported_variables(tools->export);

    return(0);
}