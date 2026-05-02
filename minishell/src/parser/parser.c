/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:11:20 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:11:02 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_token_to_list(t_token_list **token_list, t_token *current_token)
{
	t_token_list	*new_node;
	t_token_list	*temp;

	new_node = malloc(sizeof(t_token_list));
	if (!new_node)
	{
		free(current_token->value);
		free(current_token);
		return ;
	}
	new_node->token = current_token;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!*token_list)
		*token_list = new_node;
	else
	{
		temp = *token_list;
		while (temp->next)
			temp = temp->next;
		new_node->prev = temp;
		temp->next = new_node;
	}
}

void	count_tokens(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_PIPE)
			minishell->count->pipe_count++;
		else if (tmp->token->type == TOKEN_REDIRECT_IN)
			minishell->count->redir_in_count++;
		else if (tmp->token->type == TOKEN_REDIRECT_OUT)
			minishell->count->redir_out_count++;
		else if (tmp->token->type == TOKEN_APPEND)
			minishell->count->append_count++;
		else if (tmp->token->type == TOKEN_HEREDOC)
			minishell->count->heredoc_count++;
		tmp = tmp->next;
	}
}

void	compare_tokens(t_token *current_token, int *file)
{
	if (*file == 1)
	{
		current_token->type = TOKEN_FILE;
		*file = 0;
	}
	else if (ft_strcmp(current_token->value, "<") == 0)
		current_token->type = TOKEN_REDIRECT_IN;
	else if (ft_strcmp(current_token->value, ">") == 0)
		current_token->type = TOKEN_REDIRECT_OUT;
	else if (ft_strcmp(current_token->value, ">>") == 0)
		current_token->type = TOKEN_APPEND;
	else if (ft_strcmp(current_token->value, "<<") == 0)
		current_token->type = TOKEN_HEREDOC;
	else if (ft_strcmp(current_token->value, "|") == 0)
		current_token->type = TOKEN_PIPE;
	else
		current_token->type = TOKEN_WORD;
}

static void	remove_empty_unquoted_tokens_list(t_token_list **list)
{
	t_token_list	*cur;
	t_token_list	*next;

	cur = *list;
	while (cur)
	{
		next = cur->next;
		if (cur->token && cur->token->type == TOKEN_WORD
			&& cur->token->quotes == 0 && (!cur->token->value
				|| cur->token->value[0] == '\0'))
		{
			if (cur->prev)
				cur->prev->next = cur->next;
			else
				*list = cur->next;
			if (cur->next)
				cur->next->prev = cur->prev;
			if (cur->token->value)
				free(cur->token->value);
			free(cur->token);
			free(cur);
		}
		cur = next;
	}
}

void	parse_tokens(t_minishell *minishell, t_token_list *tmp)
{
	int	expect_command;
	int	expect_file;

	if (!minishell->token_list)
		return ;
	remove_empty_unquoted_tokens_list(&minishell->token_list);
	reset_counts(minishell);
	expect_command = 1;
	expect_file = 0;
	while (tmp)
	{
		compare_tokens(tmp->token, &expect_file);
		if (tmp->token->type == TOKEN_WORD && expect_command)
		{
			tmp->token->type = TOKEN_COMMAND;
			expect_command = 0;
		}
		if (is_tmp_redirect(tmp))
			expect_file = 1;
		else if (tmp->token->type == TOKEN_PIPE)
			expect_command = 1;
		tmp = tmp->next;
	}
	count_tokens(minishell);
}
