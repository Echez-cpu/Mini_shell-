/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:21:52 by pokpalae          #+#    #+#             */
/*   Updated: 2024/08/24 20:48:14 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

int				count_quotes(char *line);
int				implement_tools(t_tools *tools);
char			**ft_arrdup(char **arr);

int				minishell_loop(t_tools *tools);

t_simple_cmds	*ft_simple_cmdsnew(char **str, int num_redirections,
					t_lexer *redirections);
void			ft_simple_cmdsadd_back(t_simple_cmds **lst, t_simple_cmds *new);
void			ft_simple_cmds_rm_first(t_simple_cmds **lst);
void			ft_simple_cmdsclear(t_simple_cmds **lst);
t_simple_cmds	*ft_simple_cmdsfirst(t_simple_cmds *map);

t_lexer			*ft_lexernew(char *str, int token);
void			ft_lexeradd_back(t_lexer **lst, t_lexer *new);
void			ft_lexerdelone(t_lexer **lst, int i);
void			ft_lexerclear(t_lexer **lst);

int				token_reader(t_tools *tools);
int				add_node(char *str, t_tokens token, t_lexer **lexer_list);
t_tokens		check_token(int c);
int				handle_token(char *str, int i, t_lexer **lexer_list);

#endif
