/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:15:24 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/18 19:22:00 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_heredoc_command(t_minishell *ms,
	char **cmd, t_token_list *tmp)
{
	if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit"))
		execute_in_parent(cmd[0], ms);
	else if (tmp->token->type == TOKEN_COMMAND)
		handle_fork_and_execute(ms, cmd, tmp);
}

static void	process_heredoc_input(t_minishell *ms, char *del, int pipe_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "warning: heredoc delimited by EOF\n", 35);
			close(pipe_fd);
			free_for_exit(ms);
			exit(0);
		}
		else if (ft_strcmp(line, del) == 0)
		{
			free(line);
			close(pipe_fd);
			free_for_exit(ms);
			exit(0);
		}
		money_money(ms, &line);
		ft_putstr_fd(line, pipe_fd);
		ft_putstr_fd("\n", pipe_fd);
		free(line);
	}
}

void	heredoc_child(t_minishell *ms, char *del, int pipe_fd)
{
	int	tty_fd;

	(void)ms;
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	tty_fd = open("/dev/tty", O_RDWR);
	if (tty_fd != -1)
	{
		dup2(tty_fd, STDIN_FILENO);
		dup2(tty_fd, STDOUT_FILENO);
		close(tty_fd);
	}
	process_heredoc_input(ms, del, pipe_fd);
}
