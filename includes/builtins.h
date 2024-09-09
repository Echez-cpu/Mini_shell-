/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:20:34 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/09 01:49:15 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"
# include "parser.h"
# include <dirent.h>

void	change_path(t_tools *tools);

int		mini_echo(t_tools *tools, t_simple_cmds *simple_cmd);

int		mini_cd(t_tools *tools, t_simple_cmds *simple_cmd);

int		mini_pwd(t_tools *tools, t_simple_cmds *simple_cmd);

int		mini_export(t_tools *tools, t_simple_cmds *simple_cmd);

int		mini_unset(t_tools *tools, t_simple_cmds *simple_cmd);

int		mini_env(t_tools *tools, t_simple_cmds *simple_cmd);

int		mini_exit(t_tools *tools, t_simple_cmds *simple_cmd);

int		mini_continue(t_tools *tools, t_simple_cmds *simple_cmd);

size_t	equal_sign(char *str);
int		check_valid_identifier(char c);

// export functions
char	*get_export_var(char *export_line);
char	*get_export_val(char *export_line);
int		is_var_in_export(char **export, char *var);
char	**add_var_export(char **export, char *var, char *val);
int		show_exported_variables(char **export);

// envp functions
int		is_var_in_envp(char **envp, char *var);
int		get_envp_size(char **envp);
char	**add_var_envp(char **envp, char *var, char *val);
int		set_val_envp(char **envp, char *var, char *val);

#endif