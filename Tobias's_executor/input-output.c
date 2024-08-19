/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input-output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:53:36 by tlaukat           #+#    #+#             */
/*   Updated: 2024/06/19 16:23:01 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	set_input(char *input)
{
	int	fd;

	fd = open(input, O_RDONLY, 0777);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	dup2(fd, 0);
}

void	set_output(char *input)
{
}

void	set_append(char *input)
{
}

void	set_here_doc(char *input)
{
}
