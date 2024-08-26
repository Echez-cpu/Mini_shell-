#include "builtins.h"

int	show_exported_variables(char **export);

char *get_export_var(char *export_line)
{
	int		i;
	char	*var;

	i = 0;
	while (export_line[i] != '=' && export_line[i])
		i++;
	var = ft_substr(export_line, 0, i);
    if(!var)
    {
        perror("ft_substr: get_export_var");
        exit(-1);
    }
	return (var);
}

char *get_export_val(char *export_line)
{
    int i = 0;
    char *val;
	while (export_line[i] != '=' && export_line[i])
		i++;
	if(export_line[i] && ft_strlen(export_line+i)>3)
	{	
		i+=2;
		val = ft_substr(export_line, i, ft_strlen(export_line) - i - 1);
        if(!val)
        {
            perror("ft_substr: get_export_val");
            exit(-1);
        }
	}
	else
		val = NULL;
    return(val);
}

//0=false, if true: return-1=pos
int is_var_in_export(char **export, char *var)
{
    int i;
    char *tmp;

    i=0;
    while(export[i])
    {
        tmp = get_export_var(export[i]);
        if(ft_strncmp(tmp, var, ft_strlen(var) + 1)==0)
            return(free(tmp), i+1);
        free(tmp);
        i++;
    }
    return (0);
}

//0: AAA, 1: BBB, 2:DDD <- CCC, pos = 2
char **add_new_export_p(char **export, int pos)
{
    int i;
    char **tmp;

    if(pos == -1)
        return (export);
    tmp = (char **)malloc(sizeof(char *)*(get_envp_size(export) + 2));
    if(!tmp)
    {
        perror("malloc: add_new_export_p");
        exit(-1);
    }
    i=0;
    while(i<pos)
        tmp[i++]=export[i];
    tmp[pos]=NULL;
    while(export[i])
        tmp[(i++) +1]=export[i];
    tmp[i+1]=NULL;
    free(export);
    return tmp;
}

/*
1: Var isn't in export and val exists -> Works
2: Var isn't in export and val doen't exists -> Works
3: Var is in export and val exists -> Works
4: Var is in export and val doesn't exists -> Works
*/



char **add_var_export(char **export, char *var, char *val)
{
    int i;
    int b;
    char *export_line;
    i = is_var_in_export(export, var) - 1;
    b = 0;
    if(i==-1)
    {   
        while(export[++i] && !b)
        {
            export_line = get_export_var(export[i]);
            if(ft_strncmp(export_line, var, ft_strlen(var) + 1) >= 0)
                b = -1 - i--;
            free(export_line);
        }
        export = add_new_export_p(export, i);
    }
    else
    {
        export_line = ft_strchr(export[i], '=');
        free(export[i]);
        if(export_line=NULL)
            return(export[i]=ft_strdup(var), export);
    }
    export[i]=ft_strdup(var);
    if(val)
    {
        export[i]=gnl_strjoin(export[i], "=\"");
        export[i]=gnl_strjoin(export[i], val);
        export[i]=gnl_strjoin(export[i], "\"");
    }
    return(export);
}






























// //export_utils
// int is_var_in_export(char **export, char *var)
// {
// 	t_list *tmp;
// 	t_export *e_node;
// 	char *stmp;
// 	if(!export || !var)
// 		return(0);
	
// 	tmp = export;
// 	/*e_node = export->content;
// 	stmp = e_node->Name;
// 	write(1, stmp, 5);*/
// 	while(tmp)
// 	{
		
// 		e_node = tmp->content;
// 		stmp = e_node->Name;
// 		write(1, stmp, 5);
// 		;
// 		if(ft_strncmp(stmp, var, ft_strlen(var)+1) == 0)
// 			return(1);
		
// 		tmp = tmp->next;
		
// 	}
// 	return(0);
// }

// char *get_val_export(t_list *export, char* var)
// {
// 	t_list *tmp;
// 	t_export *e_node;
// 	if(!export || !var)
// 		return(0);
// 	tmp = export;
// 	while(tmp)
// 	{
// 		e_node = (t_export *)tmp->content;
// 		if(ft_strncmp(e_node->Name, var, ft_strlen(var)+1) == 0)
// 			return(ft_strdup(e_node->Val));
// 		tmp = tmp->next;
// 	}
// 	return(0);
// }

// int set_val_export(t_list *export, char* var, char *val)
// {
// 	t_list *tmp;
// 	t_export *e_node;
// 	if(!export || !var)
// 		return(0);
// 	tmp = export;
// 	while(tmp)
// 	{
// 		e_node = (t_export *)tmp->content;
// 		if(ft_strncmp(e_node->Name, var, ft_strlen(var)+1) == 0)
// 		{
// 			if(e_node->Val)
// 				free(e_node->Val);
// 			e_node->Val = ft_strdup(val);
// 			e_node->empty = 0;
// 			return(0);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return(0);
// }

// t_list *get_sort_export(t_list *export, char *var)
// {
// 	t_list *tmp;
// 	t_list *mv;
// 	t_export *e_node;

// 	tmp = export;
// 	while(tmp)
// 	{
// 		e_node = (t_export *)tmp->content;
// 		if(ft_strncmp(e_node->Name, var, ft_strlen(var)+1) >= 0)
// 		{
// 			mv = ft_lstnew(e_node);
// 			mv->next = tmp->next;
// 			tmp->next = mv;
// 			return(tmp);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return(ft_lstlast(export));
// }

// int add_var_export(t_list *export, char *var, char *val)
// {
// 	t_list *end;
// 	t_export *con;

// 	end = get_sort_export(export, var);
// 	end->content = (void *)con;
// 	con->Name = ft_strdup(var);
// 	con->empty = 1;
// 	if(val)
// 	{
// 		con->Val = ft_strdup(val);
// 		con->empty = 0;
// 	}
	
// 	return(0);
// }

// int is_val_empty(t_list *export, char *var)
// {
// 	t_list *tmp;
// 	t_export *e_node;
// 	if(!export || !var)
// 		return(0);
// 	tmp = export;
// 	while(tmp)
// 	{
// 		e_node = (t_export *)tmp->content;
// 		if(ft_strncmp(e_node->Name, var, ft_strlen(var)+1) == 0)
// 			return(e_node->empty);
// 		tmp = tmp->next;
// 	}
// 	return(0);
// }
// //export utils 2

// void *del_export_variable(t_export *e_node)
// {
// 	if(e_node->Name)
// 		free(e_node->Name);
// 	if(e_node->Val)
// 		free(e_node->Val);
// }

// int rem_var_export(t_list *export, char *var)
// {
// 	t_list *tmp;
// 	t_list *previous;
// 	t_export *e_node;
// 	if(!export || !var)
// 		return(0);
// 	tmp = export;
// 	while(tmp)
// 	{
		
// 		e_node = (t_export *)tmp->content;
// 		if(ft_strncmp(e_node->Name, var, ft_strlen(var)+1) == 0)
// 		{
// 			if(previous)
// 				previous->next = tmp->next;
// 			ft_lstdelone(tmp, (*del_export_variable)(e_node));
// 		}
// 		previous = tmp;
// 		tmp = tmp->next;
// 	}
// 	return(0);
// }