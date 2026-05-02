/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:56:36 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:10:16 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*skip_redirect_token(t_token_list *tmp)
{
	if (tmp->token->type == TOKEN_REDIRECT_IN
		|| tmp->token->type == TOKEN_REDIRECT_OUT
		|| tmp->token->type == TOKEN_APPEND
		|| tmp->token->type == TOKEN_HEREDOC)
	{
		tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	else
		tmp = tmp->next;
	return (tmp);
}

int	count_command_tokens(t_token_list *token_list)
{
	t_token_list	*tm;
	int				count;

	count = 0;
	tm = token_list;
	while (tm && tm->token->type != TOKEN_PIPE)
	{
		if (tm->token->type == TOKEN_COMMAND || tm->token->type == TOKEN_WORD)
		{
			count++;
			tm = tm->next;
		}
		else if (tm->token->type == TOKEN_REDIRECT_IN
			|| tm->token->type == TOKEN_REDIRECT_OUT
			|| tm->token->type == TOKEN_APPEND
			|| tm->token->type == TOKEN_HEREDOC)
		{
			tm = tm->next;
			if (tm)
				tm = tm->next;
		}
		else
			tm = tm->next;
	}
	return (count);
}

void	skip_redirect_tokens(t_token_list **tmp)
{
	while (*tmp)
	{
		if ((*tmp)->token->type == TOKEN_REDIRECT_IN
			|| (*tmp)->token->type == TOKEN_REDIRECT_OUT
			|| (*tmp)->token->type == TOKEN_APPEND
			|| (*tmp)->token->type == TOKEN_HEREDOC)
		{
			*tmp = (*tmp)->next;
			if (*tmp)
				*tmp = (*tmp)->next;
		}
		else if ((*tmp)->token->type == TOKEN_COMMAND
			|| (*tmp)->token->type == TOKEN_WORD)
			*tmp = (*tmp)->next;
		else
			break ;
	}
}

int	has_redirect_or_heredoc(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	while (tmp && tmp->token->type != TOKEN_PIPE)
	{
		if (tmp->token->type == TOKEN_HEREDOC
			|| tmp->token->type == TOKEN_APPEND
			|| tmp->token->type == TOKEN_REDIRECT_IN
			|| tmp->token->type == TOKEN_REDIRECT_OUT)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	has_input_redirect_or_heredoc(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	while (tmp && tmp->token->type != TOKEN_PIPE)
	{
		if (tmp->token->type == TOKEN_HEREDOC
			|| tmp->token->type == TOKEN_REDIRECT_IN)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
