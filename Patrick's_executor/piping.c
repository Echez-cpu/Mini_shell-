/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:12:14 by pokpalae          #+#    #+#             */
/*   Updated: 2024/08/19 14:22:56 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	parser(t_tools *tools)
{
	t_simple_cmds	*node;
	t_parser_tools	parser_tools;

	tools->simple_cmds = NULL;
	count_pipes(tools->lexer_list, tools);
	if (tools->lexer_list->token == PIPE)
		return (parser_double_token_error(tools, tools->lexer_list,
				tools->lexer_list->token));
	while (tools->lexer_list)
	{
		if (tools->lexer_list && tools->lexer_list->token == PIPE)
			ft_lexerdelone(&tools->lexer_list, tools->lexer_list->i);
		if (handle_pipe_errors(tools, tools->lexer_list->token))
			return (EXIT_FAILURE);
		parser_tools = init_parser_tools(tools->lexer_list, tools);
		node = initialize_cmd(&parser_tools);
		if (!node)
			parser_error(0, tools, parser_tools.lexer_list);
		if (!tools->simple_cmds)
			tools->simple_cmds = node;
		else
			ft_simple_cmdsadd_back(&tools->simple_cmds, node);
		tools->lexer_list = parser_tools.lexer_list;
	}
	return (EXIT_SUCCESS);
}



void	ft_lexerdelone(t_lexer **lst, int key)
{
	t_lexer	*node;
	t_lexer	*prev;
	t_lexer	*start;

	start = *lst;
	node = start;
	if ((*lst)->i == key)
	{
		ft_lexerdel_first(lst);
		return ;
	}
	while (node && node->i != key)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	ft_lexerclear_one(&node);
	*lst = start;
}



t_parser_tools	init_parser_tools(t_lexer *lexer_list, t_tools *tools)
{
	t_parser_tools	parser_tools;

	parser_tools.lexer_list = lexer_list;
	parser_tools.redirections = NULL;
	parser_tools.num_redirections = 0;
	parser_tools.tools = tools;
	return (parser_tools);
}



t_simple_cmds	*initialize_cmd(t_parser_tools *parser_tools)
{
	char	**str;
	int		i;
	int		arg_size;
	t_lexer	*tmp;

	i = 0;
	//Tobias_implement_remove_redirections_tokens(parser_tools);
	arg_size = count_args(parser_tools->lexer_list);
	str = ft_calloc(arg_size + 1, sizeof(char *));
	if (!str)
		parser_error(1, parser_tools->tools, parser_tools->lexer_list);
	tmp = parser_tools->lexer_list;
	while (arg_size > 0)
	{
		if (tmp->str)
		{
			str[i++] = ft_strdup(tmp->str);
			ft_lexerdelone(&parser_tools->lexer_list, tmp->i);
			tmp = parser_tools->lexer_list;
		}
		arg_size--;
	}
	return (ft_simple_cmdsnew(str,
			parser_tools->num_redirections, parser_tools->redirections));
}