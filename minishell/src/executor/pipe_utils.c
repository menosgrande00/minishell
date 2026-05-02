/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 09:51:03 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:10:08 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection(t_minishell *minishell)
{
	int	status;

	if (has_redirect(minishell))
	{
		minishell->exit_status = handle_redirect(minishell,
				&minishell->token_list);
		status = minishell->exit_status;
		free_for_exit(minishell);
		exit(status);
	}
}

void	close_pipes_for_segment(int i, int **fd, int pipe_count)
{
	if (i > 0)
		close(fd[i - 1][0]);
	if (i < pipe_count)
		close(fd[i][1]);
}
