/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:38:32 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:04:07 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_non_heredoc_commands(t_minishell *ms,
		t_token_list **tmp, char **cmd)
{
	char	*cmd0;

	if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit"))
	{
		if (!ft_strcmp(cmd[0], "exit"))
		{
			cmd0 = cmd[0];
			if (cmd)
				free(cmd);
			execute_in_parent(cmd0, ms);
		}
		else
			execute_in_parent(cmd[0], ms);
	}
	else if ((*tmp)->token->type != TOKEN_WORD)
		handle_fork_and_execute(ms, cmd, *tmp);
}

static int	handle_heredoc_and_commands(t_minishell *ms,
		t_token_list **tmp, char **cmd)
{
	int	saved_stdin;

	if (has_heredoc(ms))
	{
		saved_stdin = dup(STDIN_FILENO);
		if (handle_heredoc(ms, cmd))
		{
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			skip_redirect_tokens(tmp);
			return (ms->exit_status);
		}
		execute_heredoc_command(ms, cmd, *tmp);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		skip_redirect_tokens(tmp);
		return (ms->exit_status);
	}
	execute_non_heredoc_commands(ms, tmp, cmd);
	return (0);
}

int	process_single_token(t_minishell *minishell, t_token_list **tmp)
{
	char	**cmd;
	int		saved_stdin;
	int		ret;

	cmd = current_token(*tmp);
	if (has_redirect(minishell))
	{
		saved_stdin = dup(STDIN_FILENO);
		minishell->exit_status = handle_redirect(minishell, tmp);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		skip_redirect_tokens(tmp);
		if (cmd)
			free(cmd);
		return (minishell->exit_status);
	}
	ret = handle_heredoc_and_commands(minishell, tmp, cmd);
	if (cmd)
		free(cmd);
	return (ret);
}

int	execute_no_pipe(t_minishell *minishell, t_token_list *tmp)
{
	while (tmp)
	{
		process_single_token(minishell, &tmp);
		if (tmp && !has_redirect_or_heredoc(minishell))
		{
			while (tmp && (tmp->token->type == TOKEN_COMMAND
					|| tmp->token->type == TOKEN_WORD))
				tmp = tmp->next;
		}
	}
	return (minishell->exit_status);
}

int	execute_command(t_minishell *minishell)
{
	t_token_list	*tmp;
	int				ret;

	tmp = minishell->token_list;
	if (!tmp)
	{
		minishell->exit_status = 0;
		return (0);
	}
	ret = 0;
	if (is_pipeline(minishell))
		ret = execute_pipe_line(minishell);
	else
		ret = execute_no_pipe(minishell, tmp);
	return (ret);
}
