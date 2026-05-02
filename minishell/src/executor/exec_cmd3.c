/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:38:38 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/18 20:53:03 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_directory_and_permissions(t_minishell *minishell,
		char **cmd, char *path, char **env_array)
{
	struct stat	st;

	(void)env_array;
	if (stat(path, &st) == 0 && is_dot(cmd))
	{
		if (S_ISDIR(st.st_mode))
		{
			minishell->exit_status = report_is_a_directory(minishell, cmd[0]);
			return (1);
		}
		else if (!(st.st_mode & S_IXUSR))
		{
			minishell->exit_status = report_perm_denied(minishell, cmd[0]);
			return (1);
		}
	}
	return (0);
}

static int	handle_path_errors_and_exit(t_minishell *minishell, char **cmd,
		char *path, char **env_array)
{
	(void)env_array;
	if (!path)
	{
		if (is_dot(cmd))
		{
			minishell->exit_status = report_no_such_file(minishell, cmd[0]);
			return (1);
		}
		minishell->exit_status = report_cmd_not_found(minishell, cmd[0]);
		return (1);
	}
	return (0);
}

static int	handle_errors_and_exit(t_minishell *minishell, char **cmd,
	char *path, char **env_array)
{
	int	ret;

	ret = check_directory_and_permissions(minishell, cmd, path, env_array);
	if (ret)
		return (1);
	ret = handle_path_errors_and_exit(minishell, cmd, path, env_array);
	return (ret);
}

void	validate_and_execute(t_minishell *minishell, char **cmd, char *path)
{
	char	**env_array;
	int		status;

	env_array = make_env_array(minishell);
	if (handle_errors_and_exit(minishell, cmd, path, env_array))
	{
		status = minishell->exit_status;
		if (path)
			free(path);
		if (env_array)
			free_double(env_array);
		if (!minishell->tokens && cmd)
			free(cmd);
		free_for_exit(minishell);
		exit(status);
	}
	execve(path, cmd, env_array);
	free(path);
	free_double(env_array);
	if (!minishell->tokens && cmd)
		free(cmd);
	free_for_exit(minishell);
	exit(1);
}
