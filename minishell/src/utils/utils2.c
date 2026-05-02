/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:06:39 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:11:50 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (1);
	while (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	has_redirect(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	while (tmp && tmp->token->type != TOKEN_PIPE)
	{
		if (tmp->token->type == TOKEN_APPEND
			|| tmp->token->type == TOKEN_REDIRECT_IN
			|| tmp->token->type == TOKEN_REDIRECT_OUT)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	has_heredoc(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	while (tmp && tmp->token->type != TOKEN_PIPE)
	{
		if (tmp->token->type == TOKEN_HEREDOC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	is_tmp_redirect(t_token_list *tmp)
{
	int	i;

	i = 0;
	if (tmp->token->type == TOKEN_REDIRECT_IN
		|| tmp->token->type == TOKEN_REDIRECT_OUT
		|| tmp->token->type == TOKEN_APPEND
		|| tmp->token->type == TOKEN_HEREDOC)
		i = 1;
	return (i);
}

void	skip_spaces(const char *input, int *idx)
{
	while (input[*idx] == ' ' || input[*idx] == '\t')
		(*idx)++;
}
