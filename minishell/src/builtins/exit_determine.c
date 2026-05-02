/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_determine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:23:49 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:08:41 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_space_in_arg(t_minishell *minishell)
{
	char	*arg;
	char	*space_pos;
	int		len;
	char	*first_part;

	arg = minishell->token_list->next->token->value;
	space_pos = ft_strchr(arg, ' ');
	len = space_pos - arg;
	first_part = malloc(len + 1);
	ft_strlcpy(first_part, arg, len + 1);
	if (!is_numeric(first_part))
	{
		free(first_part);
		return (report_error(minishell,
				"minishell: unset: not a valid identifier", ERR_INVALID_ARG));
	}
	else
	{
		report_num_arg_req(minishell, first_part, len);
		free(first_part);
		free_for_exit(minishell);
		exit(minishell->exit_status);
	}
}

static int	handle_single_arg(t_minishell *minishell)
{
	if (minishell->token_list && minishell->token_list->next)
	{
		if (ft_strchr(minishell->token_list->next->token->value, ' '))
			return (handle_space_in_arg(minishell));
		else if (!is_numeric(minishell->token_list->next->token->value))
			return (ft_atoi(minishell->token_list->next->token->value) % 256);
		else
			return (2);
	}
	return (-1);
}

static int	process_joined_arg(t_minishell *minishell)
{
	char	*tmp;
	int		res;

	tmp = ft_strjoin(minishell->token_list->next->token->value,
			minishell->token_list->next->next->token->value);
	if (!is_numeric(tmp))
	{
		res = ft_atoi(tmp) % 256;
		free(tmp);
		return (res);
	}
	else
	{
		free(tmp);
		return (2);
	}
}

static int	handle_quoted_args(t_minishell *minishell)
{
	if (minishell->token_list && minishell->token_list->next
		&& minishell->token_list->next->next
		&& minishell->token_list->next->next->token->quotes == 1)
		return (process_joined_arg(minishell));
	else if (minishell->token_list && minishell->token_list->next
		&& minishell->token_list->next->next
		&& minishell->token_list->next->next->token->type == TOKEN_WORD)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		minishell->exit_status = 1;
		return (1);
	}
	return (-1);
}

int	determine_exit_code(t_minishell *minishell)
{
	int	exit_code;
	int	result;

	exit_code = minishell->exit_status;
	result = handle_quoted_args(minishell);
	if (result != -1)
		exit_code = result;
	else
	{
		result = handle_single_arg(minishell);
		if (result != -1)
			exit_code = result;
	}
	return (exit_code);
}
