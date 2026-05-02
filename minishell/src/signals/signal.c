/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:01:28 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:11:38 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	ft_ctrl_c(int sig)
{
	g_signal_received = sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n^C\n", 4);
	rl_redisplay();
}

void	init_signal(void)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	simple_signal_handler(int sign)
{
	g_signal_received = sign;
	if (sign == SIGINT)
		write(1, "\n", 1);
}

int	check_signal(void)
{
	int	sig;

	sig = g_signal_received;
	g_signal_received = 0;
	return (sig);
}
