/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:29:32 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/12 11:24:28 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_heredoc(t_lexer *heredoc, bool quotes, t_tools *tools,
		char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	line = readline(HEREDOC_MSG);
	while (line && ft_strncmp(heredoc->str, line, ft_strlen(heredoc->str))
		&& !gs_stop_heredoc(-1))
	{
		if (quotes == false)
			line = expander_str(tools, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_MSG);
	}
	free(line);
	if (gs_stop_heredoc(-1) || !line)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	ft_heredoc(t_tools *tools, t_lexer *heredoc, char *file_name)
{
	bool	quotes;
	int		sl;

	sl = EXIT_SUCCESS;
	if ((heredoc->str[0] == '\"' && heredoc->str[ft_strlen(heredoc->str) \
			- 1] == '\"') || (heredoc->str[0] == '\'' \
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\''))
		quotes = true;
	else
		quotes = false;
	delete_quotes_2(heredoc->str, '\"');
	delete_quotes_2(heredoc->str, '\'');
	gs_stop_heredoc(0);
	gs_in_heredoc(1);
	sl = create_heredoc(heredoc, quotes, tools, file_name);
	gs_in_heredoc(0);
	tools->heredoc = true;
	return (sl);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("build/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

int	send_heredoc(t_tools *tools, t_simple_cmds *cmd)
{
	t_lexer	*start;
	int		sl;

	start = cmd->redirections;
	sl = EXIT_SUCCESS;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == LESS_LESS)
		{
			if (cmd->hd_file_name)
				free(cmd->hd_file_name);
			cmd->hd_file_name = generate_heredoc_filename();
			sl = ft_heredoc(tools, cmd->redirections, cmd->hd_file_name);
			if (sl)
			{
				gs_error_num(130);
				return (reset_tools(tools));
			}
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}
