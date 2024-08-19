/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo-pwd-export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/06/10 14:53:44 by tlaukat           #+#    #+#             */
/*   Updated: 2024/07/10 18:35:45 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct s_export
{
	char *Name;
	char *Val;
	int empty;
} t_export;

int	echo(char **args)
{
	int i;
	int j;
	int n;

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

int	pwd(char **args)
{
	char *path;

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

// export_utils
int	is_var_in_export(t_list *export, char *var)
{
	t_list *tmp;
	t_export *e_node;
	char *stmp;
	if (!export || !var)
		return (0);

	tmp = export;
	/*e_node = export->content;
	stmp = e_node->Name;
	write(1, stmp, 5);*/
	while (tmp)
	{
		e_node = tmp->content;
		stmp = e_node->Name;
		write(1, stmp, 5);
		;
		if (ft_strncmp(stmp, var, ft_strlen(var) + 1) == 0)
			return (1);

		tmp = tmp->next;
	}
	return (0);
}

char	*get_val_export(t_list *export, char *var)
{
	t_list *tmp;
	t_export *e_node;
	if (!export || !var)
		return (0);
	tmp = export;
	while (tmp)
	{
		e_node = (t_export *)tmp->content;
		if (ft_strncmp(e_node->Name, var, ft_strlen(var) + 1) == 0)
			return (ft_strdup(e_node->Val));
		tmp = tmp->next;
	}
	return (0);
}

int	set_val_export(t_list *export, char *var, char *val)
{
	t_list *tmp;
	t_export *e_node;
	if (!export || !var)
		return (0);
	tmp = export;
	while (tmp)
	{
		e_node = (t_export *)tmp->content;
		if (ft_strncmp(e_node->Name, var, ft_strlen(var) + 1) == 0)
		{
			if (e_node->Val)
				free(e_node->Val);
			e_node->Val = ft_strdup(val);
			e_node->empty = 0;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_list	*get_sort_export(t_list *export, char *var)
{
	t_list *tmp;
	t_list *mv;
	t_export *e_node;

	tmp = export;

	e_node = (t_export *)malloc(sizeof(t_export));

	mv = ft_lstnew(e_node);

	while (tmp->next)
	{
		e_node = (t_export *)tmp->content;
		if (ft_strncmp(e_node->Name, var, 200) >= 0)
		{
			mv->next = tmp->next;
			tmp->next = mv;
			return (mv);
		}
		tmp = tmp->next;
	}
	tmp->next = mv;
	mv->next = NULL;
	return (mv);
}

int	add_var_export(t_list *export, char *var, char *val)
{
	t_list *end;
	t_export *con;

	end = get_sort_export(export, var);

	con = end->content;

	con->Name = ft_strdup(var);
	con->empty = 1;
	if (val)
	{
		con->Val = ft_strdup(val);
		con->empty = 0;
	}
	else
		con->Val = NULL;
	return (0);
}

int	is_val_empty(t_list *export, char *var)
{
	t_list *tmp;
	t_export *e_node;
	if (!export || !var)
		return (0);
	tmp = export;
	while (tmp)
	{
		e_node = (t_export *)tmp->content;
		if (ft_strncmp(e_node->Name, var, ft_strlen(var) + 1) == 0)
			return (e_node->empty);
		tmp = tmp->next;
	}
	return (0);
}
// export utils 2

void	*del_export_variable(t_export *e_node)
{
	if (e_node->Name)
		free(e_node->Name);
	if (e_node->Val)
		free(e_node->Val);
}

int	rem_var_export(t_list *export, char *var)
{
	t_list *tmp;
	t_list *previous;
	t_export *e_node;
	if (!export || !var)
		return (0);
	tmp = export;
	while (tmp)
	{
		e_node = (t_export *)tmp->content;
		if (ft_strncmp(e_node->Name, var, ft_strlen(var) + 1) == 0)
		{
			if (previous)
				previous->next = tmp->next;
			ft_lstdelone(tmp, (*del_export_variable)(e_node));
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (0);
}

// envp utils

int	is_var_in_envp(char **envp, char *var)
{
	int i;

	i = 0;
	if (!var)
		return (0);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			if (envp[i][ft_strlen(var)] == '=')
				return (1);
		i++;
	}
	return (0);
}

int	get_envp_size(char **envp)
{
	int i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	add_var_envp(char **envp, char *var, char *val)
{
	int i;
	char **new_envp;

	new_envp = (char **)malloc((get_envp_size(envp) + 2) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i] = ft_strjoin(var, "=");
	new_envp[i] = ft_strjoin(new_envp[i], val);
	i++;
	new_envp[i] = NULL;
	free(envp);
	envp = new_envp;
	return (0);
}

int	set_val_envp(char **envp, char *var, char *val)
{
	int i;

	i = 0;
	if (!var)
		return (0);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			if (envp[i][ft_strlen(var)] == '=')
			{
				free(envp[i]);
				envp[i] = malloc(ft_strlen(var) + ft_strlen(val) + 2);
				envp[i] = ft_strjoin(var, "=");
				envp[i] = gnl_strjoin(envp[i], val);
			}
		i++;
	}
	return (0);
}
// export

int	show_exported_variables(t_list *export)
{
	t_list *tmp;
	t_export *e_n;

	tmp = export;
	while (tmp)
	{
		e_n = tmp->content;
		if (e_n->empty)
			printf("declare -x %s\n", e_n->Name);
		else if (!e_n->Val)
			printf("declare -x %s=\"\"\n", e_n->Name);
		else
			printf("declare -x %s=\"%s\"\n", e_n->Name, e_n->Val);
		tmp = tmp->next;
	}
	return (1);
}

int	export_variable(char *var, char *val, t_list *export, char **envp)
{
	if (!is_var_in_export(export, var))
		return (add_var_export(export, var, val));
	if (is_val_empty(export, var) && !val)
		return (0);
	set_val_export(export, var, val);
	if (!is_var_in_envp(envp, var))
		return (add_var_envp(envp, var, val));
	set_val_envp(envp, var, val);
	return (0);
}

int	export(char **args, char **envp, t_list *exp)
{
	int i;
	int j;
	char *var;
	char *val;

	i = 1;
	if (args[1] == NULL)
		return (show_exported_variables(exp));
	while (args[i])
	{
		j = 0;
		while (args[i][j] != '=' && args[i][j])
			j++;
		var = ft_substr(args[i], 0, j);
		if (args[i][j])
		{
			j++;
			val = ft_substr(args[i], j, ft_strlen(args[i]) - j);
		}
		else
			val = NULL;
		ft_printf("%s, %s\n", var, val);
		write(1, "test\n", 5);
		if (export_variable(var, val, exp, envp) == -1)
			return (-1);
		write(1, "test end\n", 9);
		free(val);
		free(var);
		i++;
	}
	return (show_exported_variables(exp));
	return (0);
}

// end
t_export	*testassigner(void)
{
	t_export *test;
	test = (t_export *)malloc(sizeof(*test));
	test->Name = ft_strdup("Hello\n");
	test->Val = ft_strdup("export\0");
	test->empty = 0;
	return (test);
}

int	main(int argc, char **argv, char **env)
{
	t_list *exp;
	t_export *test;
	int i = 0;
	char **envp = malloc((get_envp_size(env) + 1) * sizeof(char));
	test = (t_export *)malloc(sizeof(t_export));
	/*test->Name = ft_strdup("Hello\n");
	test->Val = ft_strdup("export\0");
	test->empty = 0;
	ft_lstadd_back(exp, ft_lstnew(test));*/
	// t_export *e_node = exp->content;
	// char *tmp = ft_strdup(exp->content.Name);
	// write(1, tmp, ft_strlen(tmp));

	// add_var_export(exp, ft_strdup("PWD"), ft_strdup("YOLO!"));
	while (env[i])
	{
		envp[i] = ft_strdup(env[i]);
		i++;
	}
	envp[i] = NULL;

	test->Name = ft_strdup("OLDPWD");
	test->Val = NULL;
	test->empty = 1;
	exp = ft_lstnew(test);
	add_var_export(exp, ft_strdup("PWD"), ft_strdup("YOLO!"));
	show_exported_variables(exp);
	// add_var_export(exp, ft_strdup("PWD"), ft_strdup("YOLO!"));
	add_var_export(exp, ft_strdup("A"), ft_strdup("First!"));
	show_exported_variables(exp);
	add_var_export(exp, ft_strdup("a"), ft_strdup("Last!"));
	show_exported_variables(exp);
	add_var_export(exp, ft_strdup("Check"), ft_strdup("S!"));
	show_exported_variables(exp);
	add_var_export(exp, ft_strdup("Ass"), NULL);
	show_exported_variables(exp);
	rem_var_export(exp, ft_strdup("PWD"));
	// export(envp, envp, exp);

	if (argc == 1)
		return (0);
	if (strcmp(argv[1], "echo") == 0)
		return (echo(++argv));
	if (strcmp(argv[1], "pwd") == 0)
		return (pwd(++argv));
	if (strcmp(argv[1], "export") == 0)
		return (export(++argv, envp, exp));
	if (strcmp(argv[1], "env") == 0)
		while (*env != NULL)
			printf("%s\n", *env++);
	if (strcmp(argv[1], "exit") == 0)
		exit(0);
	return (0);
}
