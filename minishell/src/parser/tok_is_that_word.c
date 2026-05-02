/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_is_that_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:29:49 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:11:20 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	advance_word_end(const char *input, int *idx)
{
	while (input[*idx] && input[*idx] != ' ' && input[*idx] != '\t'
		&& input[*idx] != '<' && input[*idx] != '>'
		&& input[*idx] != '|' && input[*idx] != '\''
		&& input[*idx] != '"')
		(*idx)++;
}

static int	ft_create_and_validate_token_value(t_minishell *ms, int start,
	int end, t_token *tok)
{
	char	*tmp;

	tmp = ft_substr(ms->input, start, end - start);
	if (!tmp)
		return (0);
	if (money_money(ms, &tmp))
	{
		free(tmp);
		return (0);
	}
	if (!tmp || tmp[0] == '\0')
	{
		free(tmp);
		return (0);
	}
	tok->value = ft_strdup(tmp);
	tok->type = TOKEN_WORD;
	free(tmp);
	if (!tok->value)
		return (0);
	return (1);
}

static int	create_and_add_token(t_minishell *ms, int start, int end,
		t_token **tok)
{
	*tok = ft_calloc(sizeof(t_token), 1);
	if (*tok == NULL)
		return (0);
	if (!ft_create_and_validate_token_value(ms, start, end, *tok))
	{
		free(*tok);
		return (0);
	}
	add_token_to_list(&ms->token_list, *tok);
	return (1);
}

int	is_that_word(t_minishell *ms, int *i, t_token **tok, int *counter)
{
	int	start;

	while (ms->input[*i] && ms->input[*i] != '|' \
		&& ms->input[*i] != '<' && ms->input[*i] != '>')
	{
		if (*counter == 1)
			skip_spaces(ms->input, i);
		start = *i;
		advance_word_end(ms->input, i);
		if (*i - start == 0)
			break ;
		if (!create_and_add_token(ms, start, *i, tok))
			return (0);
		if (*counter == 1)
		{
			skip_spaces(ms->input, i);
			*counter = 0;
		}
	}
	return (1);
}

char	*replace_tmp(char *tmp, int *j, char *status)
{
	int		i;
	int		y;
	char	*last;

	i = 0;
	last = ft_strdup(tmp + ((*j) + 2));
	if (!last)
		return (NULL);
	while (status[i])
	{
		tmp[*j] = status[i];
		(*j)++;
		i++;
	}
	y = (*j);
	i = 0;
	while (last[i])
	{
		tmp[y] = last[i];
		y++;
		i++;
	}
	tmp[y] = '\0';
	free(last);
	return (tmp);
}
