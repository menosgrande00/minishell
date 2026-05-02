/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:01:55 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/15 18:40:05 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_command_path(t_env *envp, char **cmd)
{
	char	*path;

	path = get_path(envp, cmd[0]);
	if (!path && is_dot(cmd))
	{
		if (access(cmd[0], F_OK) == 0)
			path = ft_strdup(cmd[0]);
	}
	return (path);
}

static void	child_process_execution(char *path, char **cmd, t_minishell *ms)
{
	char	**env_array;

	set_default_signals();
	env_array = make_env_array(ms);
	if (!env_array)
	{
		free(path);
		exit(1);
	}
	if (execve(path, cmd, env_array) == -1)
	{
		free(path);
		free_double(env_array);
		perror("minishell");
		exit(126);
	}
}

static int	parent_process_wait(pid_t pid, t_minishell *minishell)
{
	int	status;
	int	sig;
	int	tty_fd;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		tty_fd = open("/dev/tty", O_RDWR);
		if (tty_fd != -1)
		{
			dup2(tty_fd, STDIN_FILENO);
			dup2(tty_fd, STDOUT_FILENO);
			close(tty_fd);
		}
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "^C\n", 3);
		minishell->exit_status = 128 + sig;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (minishell->exit_status);
}

int	execute_external_command(char **cmd, t_minishell *minishell)
{
	char	*path;
	pid_t	pid;

	path = find_command_path(minishell->envp, cmd);
	if (!path)
		return (report_cmd_not_found(minishell, cmd[0]));
	set_ignore_signals();
	pid = fork();
	if (pid == 0)
		child_process_execution(path, cmd, minishell);
	else if (pid > 0)
	{
		free(path);
		return (parent_process_wait(pid, minishell));
	}
	else
	{
		free(path);
		perror("fork");
		minishell->exit_status = 1;
	}
	return (minishell->exit_status);
}
