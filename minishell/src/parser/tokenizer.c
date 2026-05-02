/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:11:57 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:11:24 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_operator(char *str, t_token **current_token)
{
	*current_token = ft_calloc(sizeof(t_token), 1);
	if ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[1] == '<')
		|| (str[0] == '|' && str[1] == '|'))
	{
		(*current_token)->value = ft_substr(str, 0, 2);
		if (!(*current_token)->value)
		{
			free(*current_token);
			return (0);
		}
		return (2);
	}
	else if (str[0] == '|' || str[0] == '<' || str[0] == '>')
	{
		(*current_token)->value = ft_substr(str, 0, 1);
		if (!(*current_token)->value)
		{
			free(*current_token);
			*current_token = NULL;
			return (0);
		}
		return (1);
	}
	free(*current_token);
	return (0);
}

int	handle_q_and_op(t_minishell *minishell, int *i, t_token **tok, int *count)
{
	int	ret;

	if (minishell->input[*i] == '\"')
	{
		ret = double_quotes(minishell, i, tok);
		if (ret != 0)
			return (ret);
		return (0);
	}
	if (minishell->input[*i] == '\'')
	{
		ret = single_quotes(minishell, i, tok);
		if (ret != 0)
			return (ret);
		return (0);
	}
	ret = is_operator(&minishell->input[*i], tok);
	if (ret)
	{
		*count = 1;
		add_token_to_list(&minishell->token_list, *tok);
		*i += ret;
		return (0);
	}
	return (-1);
}

int	split_input(t_minishell *minishell)
{
	t_token	*token;
	int		i;
	int		ret;
	int		counter;

	counter = 1;
	i = 0;
	while (minishell->input[i])
	{
		while (minishell->input[i] == ' ' || minishell->input[i] == '\t')
			i++;
		if (!minishell->input[i])
			break ;
		ret = handle_q_and_op(minishell, &i, &token, &counter);
		if (ret > 0)
			return (ret);
		else if (ret == -1)
			is_that_word(minishell, &i, &token, &counter);
		if (!minishell->input[i - 1])
			break ;
	}
	return (0);
}

t_token_list	*tokenizer(t_minishell *minishell)
{
	if (minishell->token_list)
	{
		free_token_list(minishell->token_list);
		minishell->token_list = NULL;
	}
	if (!minishell || !(minishell)->input)
		return (NULL);
	split_input(minishell);
	return (minishell->token_list);
}
