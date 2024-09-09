/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:50:43 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/09 17:46:35 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

// int		get_error_num(void);
// int		get_in_cmd(void);
// int		get_in_heredoc(void);
// int		get_stop_heredoc(void);

// void	set_error_num(int value);
// void	set_in_cmd(int value);
// void	set_in_heredoc(int value);
// void	set_stop_heredoc(int value);

int	gs_error_num(int val);
int	gs_in_cmd(int val);
int	gs_in_heredoc(int val);
int	gs_stop_heredoc(int val);

#endif
