/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:59:46 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:10:31 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	extract_last_output_redirect(t_token_list *tmp,
	char **last_file, int *is_append)
{
	*last_file = NULL;
	*is_append = 0;
	while (tmp && tmp->token->type != TOKEN_PIPE)
	{
		if ((tmp->token->type == TOKEN_REDIRECT_OUT
				|| tmp->token->type == TOKEN_APPEND) && tmp->next)
		{
			*last_file = tmp->next->token->value;
			*is_append = (tmp->token->type == TOKEN_APPEND);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

static int	setup_input_redirections(t_minishell *minishell, char *input_file)
{
	int	input_fd;

	if (input_file)
	{
		input_fd = open(input_file, O_RDONLY);
		if (input_fd == -1)
		{
			write(2, "minishell: ", 11);
			write(2, input_file, ft_strlen(input_file));
			write(2, ": No such file or directory\n", 28);
			minishell->exit_status = 1;
			exit (1);
		}
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	return (0);
}

static int	setup_output_redirections(t_minishell *minishell)
{
	char	*last_file;
	int		is_append;
	int		output_fd;

	last_file = NULL;
	is_append = 0;
	extract_last_output_redirect(minishell->token_list, &last_file, &is_append);
	if (last_file)
	{
		if (is_append)
			output_fd = open(last_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			output_fd = open(last_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd == -1)
		{
			report_perm_denied(minishell, last_file);
			return (1);
		}
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	return (0);
}

int	setup_all_redirection(t_minishell *ms, char *input_file)
{
	ms->exit_status = setup_input_redirections(ms, input_file);
	if (ms->exit_status)
		return (1);
	if (setup_output_redirections(ms))
		return (1);
	return (0);
}
