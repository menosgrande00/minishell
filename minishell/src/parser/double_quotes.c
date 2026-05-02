/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:37:01 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/14 22:24:36 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_merge_logic(t_minishell *ms, int *i, t_token **tok, int j)
{
	if (ms->input[j - 1] != ' ')
	{
		merge_with_previous_token(ms, tok);
		if (ms->input[*i + 1] != ' ' && ms->input[*i + 1] != '\0')
		{
			handle_after_quote_text(ms, i, j);
			while (ms->input[*i] != ' ' && ms->input[*i] != '\0')
				(*i)++;
		}
	}
	else if (ms->input[*i + 1] != ' ' && ms->input[*i + 1] != '\0')
	{
		if (*tok)
		{
			if ((*tok)->value)
				free((*tok)->value);
			free(*tok);
			*tok = NULL;
		}
		remove_quotes_from_input(ms, j, *i, '"');
		*i = j - 2;
	}
}

int	handle_quote_merging(t_minishell *ms, int *i, t_token **tok, int j)
{
	if (j > 0 && ms->input[j - 1] == '|' && ms->input[*i + 1] != '"')
	{
		add_token_to_list(&ms->token_list, *tok);
		remove_quotes_from_input(ms, j, *i, '"');
		*i = j + ft_strlen((*tok)->value);
		return (0);
	}
	if (ms->input[j - 1] == ' '
		&& (ms->input[*i + 1] == ' ' || ms->input[*i + 1] == '\0'))
	{
		add_token_to_list(&ms->token_list, *tok);
		(*i)++;
		return (0);
	}
	quote_merge_logic(ms, i, tok, j);
	(*i)++;
	return (0);
}

static int	create_quote_token(t_minishell *ms, int start, int i,
				t_token **current_token)
{
	char	*tmp;

	tmp = ft_substr(ms->input, start, i - start);
	if (!tmp)
		return (1);
	*current_token = ft_calloc(sizeof(t_token), 1);
	if (!*current_token)
	{
		free(tmp);
		return (1);
	}
	(*current_token)->value = tmp;
	(*current_token)->type = TOKEN_WORD;
	(*current_token)->quotes = 1;
	return (0);
}

int	process_quote_content(t_minishell *minishell, int *i, int *start)
{
	int	ret;

	while (minishell->input[*i] && minishell->input[*i] != '"')
	{
		if (minishell->input[*i] == '$' && minishell->input[*i + 1]
			&& minishell->input[*i + 1] != ' ')
		{
			ret = handle_dollar_in_quotes(minishell, i, start);
			if (ret == -1)
				return (1);
			continue ;
		}
		(*i)++;
	}
	if (minishell->input[*i] != '"')
	{
		write(2, "syntax error: unclosed quote\n", 29);
		minishell->exit_status = 2;
		return (1);
	}
	return (0);
}

int	double_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
	int	start;
	int	j;
	int	ret;

	j = (*i);
	start = ++(*i);
	ret = process_quote_content(minishell, i, &start);
	if (ret)
		return (ret);
	ret = create_quote_token(minishell, start, *i, current_token);
	if (ret)
		return (1);
	ret = handle_quote_merging(minishell, i, current_token, j);
	if (ret)
	{
		if (*current_token)
		{
			if ((*current_token)->value)
				free((*current_token)->value);
			free(*current_token);
			*current_token = NULL;
		}
	}
	return (ret);
}
