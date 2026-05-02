/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:15:21 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/18 19:33:11 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_child_process(t_minishell *ms, char *dl, int write_fd,
		char **cmd)
{
	if (cmd)
		free(cmd);
	heredoc_child(ms, dl, write_fd);
	exit(0);
}

static int	setup_heredoc(t_minishell *ms, char *dl, int write_fd, char **cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		ft_heredoc_child_process(ms, dl, write_fd, cmd);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			ms->exit_status = 130;
			return (-1);
		}
		ms->exit_status = 0;
	}
	return (0);
}

int	handle_heredoc(t_minishell *ms, char **cmd)
{
	t_token_list	*tmp;
	int				p_fd[2];

	set_data(ms);
	pipe(p_fd);
	signal(SIGINT, SIG_IGN);
	tmp = ms->token_list;
	while (tmp && tmp->token->type != TOKEN_PIPE)
	{
		if (tmp->token->type == TOKEN_HEREDOC && tmp->next)
		{
			if (setup_heredoc(ms, tmp->next->token->value, p_fd[1], cmd) == -1)
			{
				close(p_fd[0]);
				close(p_fd[1]);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	close(p_fd[1]);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	init_signal();
	return (0);
}
