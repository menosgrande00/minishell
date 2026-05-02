/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:38:23 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/13 16:56:36 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	report_no_such_file(t_minishell *minishell, const char *cmd)
{
	write(2, "minishell: ", 11);
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, ": No such file or directory\n", 28);
	minishell->exit_status = ERR_NO_FILE;
	return (ERR_NO_FILE);
}

int	report_perm_denied(t_minishell *minishell, const char *cmd)
{
	write(2, "minishell: ", 11);
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, ": Permission denied\n", 20);
	minishell->exit_status = ERR_PERMISSION_DENIED;
	return (ERR_PERMISSION_DENIED);
}

int	report_is_a_directory(t_minishell *minishell, const char *cmd)
{
	write(2, "minishell: ", 11);
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, ": Is a directory\n", 17);
	minishell->exit_status = ERR_PERMISSION_DENIED;
	return (ERR_PERMISSION_DENIED);
}
