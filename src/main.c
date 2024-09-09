/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:09:04 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/09 17:56:08 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;

	if (argc != 1 || argv[1])
	{
		printf("\033[1;31mThis program does not accept any arguments!\n");
		return (1);
	}
	tools.envp = ft_arrdup(envp);
	tools.export = (char **)malloc(sizeof(char *));
	tools.export[0] = NULL;
	find_pwd(&tools);
	implement_tools(&tools);
	add_env_to_export(&tools);
	printf("\n%s\n\n", WELCOME_MSG);
	minishell_loop(&tools);
	return (0);
}
