/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:22:46 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:08:30 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_echo_flags(char **cmd, int *no_newline)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 2;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
		{
			*no_newline = 1;
			i++;
		}
		else
			break ;
	}
	return (i);
}

static void	print_echo_args(char **cmd, int start_index)
{
	int	first;
	int	i;

	i = start_index;
	first = 1;
	while (cmd[i] && !is_redirection(cmd[i]))
	{
		if (!first)
			write(1, " ", 1);
		write(1, cmd[i], ft_strlen(cmd[i]));
		first = 0;
		i++;
	}
}

int	ft_echo_from_cmd_array(char **cmd)
{
	int	i;
	int	no_newline;

	no_newline = 0;
	i = process_echo_flags(cmd, &no_newline);
	print_echo_args(cmd, i);
	if (!no_newline)
		write(1, "\n", 1);
	return (0);
}
