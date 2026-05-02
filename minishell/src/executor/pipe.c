/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:53:04 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/15 22:43:19 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_all_pipes(int **fd, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipe(fd[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_setup_pipeline(t_minishell *minishell, int ***fd, pid_t **pids)
{
	minishell->exit_status = malloc_fd_and_pid(fd, pids, minishell);
	if (minishell->exit_status)
		return (1);
	if (open_all_pipes(*fd, minishell->count->pipe_count))
		return (1);
	return (0);
}

static void	ft_cleanup_and_wait(t_minishell *minishell, int **fd, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < minishell->count->pipe_count)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < minishell->count->pipe_count + 1)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
		i++;
	}
	i = -1;
	while (++i < minishell->count->pipe_count)
		free(fd[i]);
	free(fd);
	free(pids);
}

int	execute_pipe_line(t_minishell *minishell)
{
	int		**fd;
	pid_t	*pids;
	int		heredoc_status;

	if (ft_setup_pipeline(minishell, &fd, &pids) != 0)
		return (1);
	set_ignore_signals();
	heredoc_status = processor(minishell, pids, fd);
	if (heredoc_status)
	{
		free_fd_and_pids(fd, pids, minishell->count->pipe_count);
		return (1);
	}
	ft_cleanup_and_wait(minishell, fd, pids);
	return (0);
}
