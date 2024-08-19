/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:15:34 by pokpalae          #+#    #+#             */
/*   Updated: 2024/08/19 14:42:20 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



int	handle_pipe_errors(t_tools *tools, t_tokens token)
{
	if (token == PIPE)
	{
		parser_double_token_error(tools, tools->lexer_list,
			tools->lexer_list->token);
		return (EXIT_FAILURE);
	}
	if (!tools->lexer_list)
	{
		parser_error(0, tools, tools->lexer_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


void	count_pipes(t_lexer *lexer_list, t_tools *tools)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	tools->pipes = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			tools->pipes++;
		tmp = tmp->next;
	}
}




t_simple_cmds	*ft_simple_cmdsnew(char **str,
	int num_redirections, t_lexer *redirections)
{
	t_simple_cmds	*new_element;

	new_element = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->builtin = builtin_arr(str[0]);
	new_element->hd_file_name = NULL;
	new_element->num_redirections = num_redirections;
	new_element->redirections = redirections;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}




void	ft_simple_cmdsadd_back(t_simple_cmds **lst, t_simple_cmds *new)
{
	t_simple_cmds	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

