/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:20:34 by pokpalae          #+#    #+#             */
/*   Updated: 2024/08/24 21:10:26 by pokpalae         ###   ########.fr       */
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

#endif