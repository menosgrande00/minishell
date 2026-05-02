/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 09:23:07 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:11:30 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "> ^C\n", 5);
	free_for_exit(get_data());
	exit(130);
}

static	t_minishell	*global_ms(t_minishell *ms)
{
	static t_minishell	*global_ms;

	if (ms)
		global_ms = ms;
	else
		return (global_ms);
	return (ms);
}

void	set_data(t_minishell *ms)
{
	global_ms(ms);
}

t_minishell	*get_data(void)
{
	return (global_ms(NULL));
}
