/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:58:39 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:10:21 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_counts(t_minishell *ms)
{
	int	i;

	i = ms->count->redir_in_count + ms->count->redir_out_count
		+ ms->count->append_count + ms->count->heredoc_count;
	return (i);
}

static void	malloc_pid_redirect(int ***fd, pid_t **pids, t_minishell *ms)
{
	int	i;

	i = -1;
	*pids = ft_calloc(sizeof(pid_t), (redirect_counts(ms) + 1));
	if (!*pids)
		return ;
	*fd = (int **)ft_calloc(2, sizeof(int *));
	while (++i < 2)
	{
		(*fd)[i] = (int *)ft_calloc(2, sizeof(int));
		if (!(*fd)[i])
		{
			while (i-- >= 0)
				free((*fd)[i]);
			free(*fd);
			free(*pids);
			*fd = NULL;
			*pids = NULL;
			return ;
		}
	}
}

static int	run_redirection_process(t_minishell *ms, t_token_list **token_list,
										t_red_files *files)
{
	int	exit_status;

	exit_status = extract_redirect_files(*token_list, &files->input,
			&files->output, &files->append);
	if (exit_status != 0)
		return (exit_status);
	exit_status = setup_all_redirection(ms, files->input);
	if (exit_status != 0)
		return (exit_status);
	exit_status = execute_redirect_child(ms);
	return (exit_status);
}

static void	restore_and_cleanup(int saved_stdin, int saved_stdout,
								int **fd, pid_t *pids)
{
	int	i;

	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	if (pids)
		free(pids);
	if (fd)
	{
		i = 0;
		while (i < 2)
		{
			if (fd[i])
				free(fd[i]);
			i++;
		}
		free(fd);
	}
}

int	handle_redirect(t_minishell *ms, t_token_list **token_list)
{
	int			**fd;
	pid_t		*pids;
	int			saved_stdin;
	int			saved_stdout;
	t_red_files	files;

	files.input = NULL;
	files.output = NULL;
	files.append = NULL;
	fd = NULL;
	pids = NULL;
	malloc_pid_redirect(&fd, &pids, ms);
	if (!fd || !pids)
	{
		if (fd)
			restore_and_cleanup(0, 0, fd, NULL);
		if (pids)
			free(pids);
		return (1);
	}
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	ms->exit_status = run_redirection_process(ms, token_list, &files);
	restore_and_cleanup(saved_stdin, saved_stdout, fd, pids);
	return (ms->exit_status);
}
