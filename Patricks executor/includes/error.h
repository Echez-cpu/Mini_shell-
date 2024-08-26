/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:20:53 by pokpalae          #+#    #+#             */
/*   Updated: 2024/08/24 21:22:18 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"
# include "parser.h"

void	parser_error(int error, t_tools *tools, t_lexer *lexer_list);
int		parser_double_token_error(t_tools *tools, t_lexer *lexer_list,
			t_tokens token);
void	lexer_error(int error, t_tools *tools);
int		cmd_not_found(char *str);
int		export_error(char *c);

int		ft_error(int error, t_tools *tools);

#endif