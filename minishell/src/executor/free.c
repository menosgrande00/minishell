/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:50:19 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/14 17:46:50 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	free_double(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

void	free_env_list(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_token_list(t_token_list *list)
{
	t_token_list	*tmp;
	t_token_list	*head;

	if (!list)
		return ;
	head = list;
	while (head->prev)
		head = head->prev;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->token)
		{
			if (tmp->token->value)
				free(tmp->token->value);
			free(tmp->token);
		}
		free(tmp);
	}
}

int	free_for_exit(t_minishell *minishell)
{
	if (minishell->token_list)
		free_token_list(minishell->token_list);
	if (minishell->envp)
		free_env_list(minishell->envp);
	if (minishell->count)
		free(minishell->count);
	if (minishell->input)
		free(minishell->input);
	if (minishell->export)
		free_double(minishell->export);
	if (minishell->tokens)
		free_double(minishell->tokens);
	free(minishell);
	return (0);
}
