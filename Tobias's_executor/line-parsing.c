/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line-parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:53:46 by tlaukat           #+#    #+#             */
/*   Updated: 2024/06/25 17:57:08 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum s_tokens
{
	PIPE = 1,
	LESSLESS,
	LESS,
	GREAT,
	GREATGREAT
}				t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

typedef struct s_tools
{
	char					*args;
	char					**paths;
	char					**envp;
	char    				**export;
	struct s_simple_cmds	*simple_cmds;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
	int						*pid;
	bool					heredoc;
	bool					reset;
}	t_tools;

size_t	ft_strlcpy(char *d, const char *s, size_t n)
{
	size_t	t;
	size_t	i;

	t = 0;
	i = 0;
	if (n == 0)
		return ((size_t)strlen(s));
	while (s[t] != '\0')
		t++;
	while (i < n - 1 && s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	if (i < n)
		d[i] = '\0';
	return (t);
}

void	ft_free(char **args, int i)
{
	int	j;

	j = 0;
	while (j < i || (i == -1 && args[j]))
	{
		free(args[j]);
		j++;
	}
	free(args);
}

int	skip_quotes(char *command_line)
{
	int	i;

	i = 0;
	if (*command_line == 34) //"
		while (command_line[i] != 34 && command_line[i])
			i++;
	else if (*command_line == 39) //'
		while (command_line[i] != 39 && command_line[i])
			i++;
	return (i);
}

int	count_args(char *command_line)
{
	int	n;
	int	quote_lock;

	n = 0;
	quote_lock = 0;
	while (*command_line)
	{
		while (*command_line == 32 && *command_line)
			command_line++;
		if (*command_line)
			n++;
		while (*command_line != 32 && *command_line)
		{
			if (*command_line == 34 && quote_lock != 1)
				quote_lock = 2 - quote_lock;
			if (*command_line == 39 && quote_lock != 2)
				quote_lock = 1 - quote_lock;
			command_line++;
			if (quote_lock)
				while (*command_line == 32)
					command_line++;
		}
	}
	return ((quote_lock == 0) * n + (quote_lock != 0) * -1);
}

int	get_args_loop(char *command_line, int i, int *quote_lock, char **args)
{
	char	*start;

	i = 0;
	while (*command_line)
	{
		while (*command_line == 32 && *command_line)
			command_line++;
		if (*command_line)
			start = command_line;
		while (*command_line != 32 && *command_line)
		{
			if (*command_line == 34 && *quote_lock != 1)
				*quote_lock = 2 - *quote_lock;
			if (*command_line == 39 && *quote_lock != 2)
				*quote_lock = 1 - *quote_lock;
			command_line++;
			if (*quote_lock != 0)
				while (*command_line == 32)
					command_line++;
		}
		args[i] = (char *)ft_calloc(command_line - start + 2, 1);
		if (args[i] == NULL)
			return (ft_free(args, i), 1);
		ft_strlcpy(args[i], start, (command_line - start) + 1);
		i++;
	}
	return (0);
}

char	**get_args(char *command_line)
{
	int		i;
	int		quote_lock;
	char	**args;

	quote_lock = 0;
	i = count_args(command_line);
	if (i == -1)
		return (NULL);
	args = (char **)ft_calloc((i + 1), sizeof(char *));
	if (args == NULL)
		return (NULL);
	args[i] = NULL;
	if (get_args_loop(command_line, i, &quote_lock, args))
		return (NULL);
	return (args);
}

int has_vars(char *arg)
{
	int quote_lock;
	int i;

	quote_lock = 0;
	i=0;
	while(arg[i])
	{
		if (arg[i] == 34 &&quote_lock != 1) 
				quote_lock = 2 - quote_lock;
		if (arg[i] == 39 && quote_lock != 2)
				quote_lock = 1 - quote_lock;
		if (arg[i] == '$' && quote_lock != 1 && arg[i + 1] != '$' && arg[i + 1])
			return(i);
		i++;
	}
	return 0;
}

char *get_val_export(t_list *export, char* var){return NULL;} //importiert

int get_var_len(char *arg, int pos)
{
	int len;
	int cur;

	len = 1;
	cur = arg[pos + len];
	if(!(ft_isdigit(cur)))
		while(ft_isalnum(cur) || cur == '_')
		{
			len++;
			cur = arg[pos + len];
		}
	else
		len++;
	return(len);
}

char *replace(char *str, char *var, int start, int length) 
{
	int var_len;
	size_t len;
	char *new;

	var_len = 0;
	if(var)
		var_len = ft_strlen(var);
	len = strlen(str) - length + var_len + 1; 
    new = (char*)malloc(len);
    if (new == NULL) 
        return (perror("parsing: replace"), NULL);
    ft_strlcpy(new, str, start + 1); 
	if(var)
    	ft_strlcpy(new + start, var, len - start);
    ft_strlcpy(new + start + var_len, str + start + length, len - start - var_len);
	if(var)
    	free(var);
    return new;
}

char *change_arg(char *arg, int pos, t_list *export)
{
	int len;
	char *val;
	char *new;

	
	len = get_var_len(arg, pos);
	new = malloc(len);
	ft_strlcpy(new, arg + pos, len);
	val = get_val_export(export, new);
	free(new);
	new = replace(arg, val, pos, len);
	return(free(arg), new);
}

int change_vars(char **args, t_list *export)
{
	int i = 0;
	while(args[i])
	{
		while(has_vars(args[i]))
			args[i] = change_arg(args[i], has_vars(args[i]), export);
		i++;
	}
}

int	quote_count_line(char *line)
{
	int	n;
	int	quote_lock;

	n = 0;
	quote_lock = 0;
	while (*line)
	{
		n++;
		if (*line == 34 && quote_lock != 1) //"
		{
			quote_lock = 2 - quote_lock;
			n--;
		}
		if (*line == 39 && quote_lock != 2) //'
		{
			quote_lock = 1 - quote_lock;
			n--;
		}
		line++;
	}
	return (n);
}

char	*rem_quotes_loop(char *line)
{
	int		i;
	int		skip;
	int		quote_lock;
	char	*temp;

	temp = (char *)ft_calloc(quote_count_line(line) + 1, 1);
	if (temp == NULL)
		return (NULL);
	i = 0;
	quote_lock = 0;
	while (*line)
	{
		skip = 0;
		if (*line == 34 && quote_lock != 1) //"
			quote_lock = 2 - quote_lock + skip++;
		if (*line == 39 && quote_lock != 2) //'
			quote_lock = 1 - quote_lock + skip++;
		if (!skip)
			temp[i++] = *line;
		line++;
	}
	return (temp);
}

char	**rem_quotes(char **args)
{
	int		k;
	char	*temp;

	k = 0;
	while (args[k])
	{
		temp = rem_quotes_loop(args[k]);
		if (temp == NULL)
			return (ft_free(args, -1), NULL);
		free(args[k]);
		args[k] = temp;
		k++;
	}
	return (args);
}

char **append_map(char **map, char *str)
{
	int i;
	char **new;

	i = 0;
	while(map[i])
		i++;
	new = malloc(sizeof(char*)*(i+2));
	i = 0;
	while(map[i])
		new[i]=map[i++];
	new[i]=str;
	free(map);
	return(new);
}

int not_first_lexer(t_tools *tools, args, i)
{
	t_lexer *lexer;
	t_lexer new;
	lexer = tools->lexer_list;
	t_lexer *lexer;
	lexer = tools->lexer_list;
	while(lexer->next)
		lexer = lexer->next;
	new = malloc(sizeof(t_lexer));
	lexer->next = &new;
	if(i=-1)
		return(new.token = PIPE, 0);
	else if(!ft_strncmp(args[i], "<", 2)) 
		new.token = LESS;
	else if(!ft_strncmp(args[i], ">", 2)) 
		new.token = GREAT;
	else if(!ft_strncmp(args[i], "<<", 3)) 
		new.token = LESSLESS;
	else if(!ft_strncmp(args[i], ">>", 3))
		new.token = GREATGREAT;
	else
		new.str = rem_quotes_loop(args[i]);
	if(!new.str)
		add_lexer(tools, args, i+1);
	return(1);
}

int add_lexer(t_tools *tools, args, i)
{
	t_lexer *lexer;
	lexer = tools->lexer_list;
	while(lexer->next)
		lexer = lexer->next;
	if(!lexer->token && !lexer->str)
		return(not_first_lexer(tools, args, i));
	while(lexer->next)
		lexer = lexer->next;
	if(i=-1)
		return(lexer->token = PIPE, 0);
	else if(!ft_strncmp(args[i], "<", 2)) 
		lexer->token = LESS;
	else if(!ft_strncmp(args[i], ">", 2)) 
		lexer->token = GREAT;
	else if(!ft_strncmp(args[i], "<<", 3)) 
		lexer->token = LESSLESS;
	else if(!ft_strncmp(args[i], ">>", 3))
		lexer->token = GREATGREAT;
	else
		lexer->str = rem_quotes_loop(args[i]);
	if(!lexer->str)
		add_lexer(tools, args, i+1);
	return(0);
}

char **add_pipe(t_tools *tools)
{
	t_simple_cmds *cmds;
	t_simple_cmd new;

	char **ret;
	
	cmds = tools->simple_cmds;
	while(cmds->next)
		cmds = cmds->next;
	new = malloc(sizeof(t_simple_cmds));
	cmds->next = &new;
	add_lexer(t_tools *tools, NULL, -1);
	ret = ft_calloc(1, sizeof(char*));
	return ret;
}

int put_into_tools(char**args, t_tools *tools)
{
	int i;
	t_simple_cmds cmds;
	t_lexer lexer;
	char **map;
	
	map = ft_calloc(1, sizeof(char*));
	cmds = malloc(sizeof(t_simple_cmds));
	cmds.str=map;
	lexer = malloc(sizeof(t_lexer));
	tools->simple_cmds = &cmds;
	tools->lexer_list = &lexer;
	i = -1;
	while(args[++i])
	{
		if(!ft_strncmp(args[i], "<", 2), !ft_strncmp(args[i], ">", 2)) 
			add_lexer(t_tools *tools, args, i);
		else if(!ft_strncmp(args[i], "<<", 3), !ft_strncmp(args[i], ">>", 3))
			add_lexer(t_tools *tools, args, i);
		else if(!ft_strncmp(args[i], "|", 2))
			map = add_pipe(tools);
		else
			map = append_map(map, rem_quotes_loop(args[i]));
	}
	return(0);
}

int	command_parsing(char *command_line, t_tools *tools)
{
	int		i;
	char	**args;

	args = get_args(command_line);
	if (args == NULL)
		return (1);
	i = change_vars(args, t_tools->export);
	if (i == 1)
		return (1);
	args = rem_quotes(args);
	if (args == NULL)
		return (1);
	put_into_tools(args, tools);
	i = 0;
	while (args[i])
	{
		printf("%d:%s\n", i, args[i]);
		i++;
	}
	return (ft_free(args, -1), 0);
}



int	main(int argc, char**argv, char**env)
{
	char	*line;
	
	t_tools *tools;

	line = readline("minishell> ");
	return (command_parsing(line, tools));
}

/*
🗸 Schritt1: "$Hello"'World"' Word -> ["$Hello"'World"'] [Word]
	//In Array splitten
✗ Schritt2: ["$Hello"'World"'] [Word] -> ["Bye"'World"'] [Word]
	//Variablen und Sonderzeichen austauschen
🗸 Schritt3: ["Bye"'World"'] [Word] -> [ByeWorld"] [Word] //Quotes lösen
~ Schritt4: Auführen! / weitergeben...
*/
