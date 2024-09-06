/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:37:37 by tlaukat           #+#    #+#             */
/*   Updated: 2024/02/14 18:44:32 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef MAX_FD
#  define MAX_FD 4000
# endif
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *str);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char const *s2);
void	*gnl_calloc(size_t count, size_t size);

#endif
