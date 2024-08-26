/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:21:04 by pokpalae          #+#    #+#             */
/*   Updated: 2024/08/24 21:03:48 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"
# include "parser.h"
# include "state.h"
# include <sys/types.h>
# include <sys/wait.h>
# define HEREDOC_MSG "> "

int				check_outfile(t_lexer *redirections);
int				check_infile(t_lexer *redirections);
int				handle_redirections(t_simple_cmds *cmd, t_tools *tools);
int				check_redirections(t_simple_cmds *cmd);

int				executor(t_tools *tools);
t_simple_cmds	*call_expander(t_tools *tools, t_simple_cmds *cmd);
int				pipe_wait(int *pid, int amount);

int				find_cmd(t_simple_cmds *cmd, t_tools *tools);
void			handle_cmd(t_simple_cmds *cmd, t_tools *tools);
void			dup_cmd(t_simple_cmds *cmd, t_tools *tools, int end[2],
					int fd_in);
void			single_cmd(t_simple_cmds *cmd, t_tools *tools);

int				send_heredoc(t_tools *tools, t_simple_cmds *cmd);

#endif