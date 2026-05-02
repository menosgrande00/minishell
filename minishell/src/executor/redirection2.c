/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:58:58 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/14 19:32:52 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_redirect(t_token_list *tmp, char **input_file)
{
	int	fd;

	if (!tmp->next)
	{
		write(2, "minishell: No such file or directory\n", 37);
		return (2);
	}
	fd = open(tmp->next->token->value, O_RDONLY);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		write(2, tmp->next->token->value,
			ft_strlen(tmp->next->token->value));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	close(fd);
	*input_file = tmp->next->token->value;
	return (0);
}

static int	handle_output_redirect(t_token_list *tmp, char **output_file,
									int is_append)
{
	int	fd;
	int	flags;

	if (!tmp->next)
	{
		write(2, "minishell: No such file or directory\n", 37);
		return (2);
	}
	if (is_append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(tmp->next->token->value, flags, 0644);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		write(2, tmp->next->token->value,
			ft_strlen(tmp->next->token->value));
		write(2, ": Permission denied\n", 20);
		return (1);
	}
	close(fd);
	*output_file = tmp->next->token->value;
	return (0);
}

static int	process_redirect_token(t_token_list **tmp, char **input_file,
									char **output_file, char **append_file)
{
	int	result;

	if ((*tmp)->token->type == TOKEN_REDIRECT_IN)
	{
		result = handle_input_redirect(*tmp, input_file);
		if (result)
			return (result);
		*tmp = (*tmp)->next;
	}
	else if ((*tmp)->token->type == TOKEN_REDIRECT_OUT)
	{
		result = handle_output_redirect(*tmp, output_file, 0);
		if (result)
			return (result);
		*tmp = (*tmp)->next;
	}
	else if ((*tmp)->token->type == TOKEN_APPEND)
	{
		result = handle_output_redirect(*tmp, append_file, 1);
		if (result)
			return (result);
		*tmp = (*tmp)->next;
	}
	return (0);
}

int	extract_redirect_files(t_token_list *tmp, char **input_file,
							char **output_file, char **append_file)
{
	int	result;

	while (tmp && tmp->token->type != TOKEN_PIPE)
	{
		result = process_redirect_token(&tmp, input_file,
				output_file, append_file);
		if (result)
			return (result);
		tmp = tmp->next;
	}
	return (0);
}
