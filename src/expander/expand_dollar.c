/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pokpalae <pokpalae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:10:07 by pokpalae          #+#    #+#             */
/*   Updated: 2024/09/10 15:03:59 by pokpalae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	handle_digit_after_dollar(int j, char *str)
{
	int	i;

	i = j;
	if (str[j] == '$')
	{
		if (ft_isdigit(str[j + 1]) == 1)
		{
			j += 2;
		}
	}
	return (j - i);
}

char	*process_quotes(char *str, t_quote_state *state)
{
	if (str[state->j] == '\'' && state->in_double_quote == 0)
		state->in_single_quote = !state->in_single_quote;
	else if (str[state->j] == '"' && state->in_single_quote == 0)
		state->in_double_quote = !state->in_double_quote;
	return (NULL);
}

char	*process_dollar_sign(t_tools *tools, char *str, t_quote_state *state,
		char *tmp)
{
	char	*tmp2;
	char	*tmp3;

	if (!state->in_single_quote)
		state->j += handle_digit_after_dollar(state->j, str);
	if (!state->in_single_quote && str[state->j] == '$' && str[state->j
			+ 1] == '?')
		state->j += question_mark(&tmp);
	else if (!state->in_single_quote && str[state->j] == '$' && str[state->j
			+ 1] != ' ' && str[state->j + 1] != '"' && str[state->j
			+ 1] != '\0')
		state->j += loop_if_dollar_sign(tools, str, &tmp, state->j);
	else
	{
		tmp2 = char_to_str(str[(state->j)++]);
		tmp3 = ft_strjoin(tmp, tmp2);
		free(tmp);
		tmp = tmp3;
		free(tmp2);
	}
	return (tmp);
}

char	*detect_dollar_sign(t_tools *tools, char *str)
{
	t_quote_state	state;
	char			*tmp;

	state.in_single_quote = 0;
	state.in_double_quote = 0;
	state.j = 0;
	tmp = ft_strdup("\0");
	while (str[state.j])
	{
		process_quotes(str, &state);
		tmp = process_dollar_sign(tools, str, &state, tmp);
	}
	return (tmp);
}
