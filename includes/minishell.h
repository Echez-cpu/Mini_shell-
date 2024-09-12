/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:21:19 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/12 11:13:40 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include "color.h"
# include "error.h"
# include "executor.h"
# include "includes/get_next_line_bonus.h"
# include "includes/libft.h"
# include "lexer.h"
# include "parser.h"
# include "state.h"
# include "utils.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		parse_envp(t_tools *tools);
int		add_env_to_export(t_tools *tools);
int		find_pwd(t_tools *tools);
int		reset_tools(t_tools *tools);
void	init_stri(int i, int j, t_tools *tools);
char	**expander(t_tools *tools, char **str);
char	*expander_str(t_tools *tools, char *str);
size_t	dollar_sign(char *str);
char	*char_to_str(char c);
int		after_dol_lenght(char *str, int j);
void	free_things(char *tmp2, t_tools *tools, int i);
void	print_parser(t_simple_cmds simple_cmds);
char	*delete_quotes_value(char *str);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	init_signals(void);
char	*delete_quotes(char *str, char c);
char	*delete_quotes_2(char *str, char c);
char	*delete_quotes_export(char *str, char c);
int		question_mark(char **tmp);
void	free_arr(char **arr);
char	*detect_dollar_sign(t_tools *tools, char *str);
int		loop_if_dollar_sign(t_tools *tools, char *str, char **tmp, int j);
int		(*builtin_arr(char *str))(t_tools *tools, t_simple_cmds *simple_cmd);
void	free_tools(t_tools *tools);

typedef struct s_quote_state
{
	int	in_single_quote;
	int	in_double_quote;
	int	j;
}		t_quote_state;

#endif
