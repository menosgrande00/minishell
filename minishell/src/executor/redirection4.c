/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:01:03 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:10:35 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtin_with_redirect(char **cmd, t_minishell *minishell)
{
	if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(minishell));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo_from_cmd_array(cmd));
	else if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit"))
		execute_in_parent(cmd[0], minishell);
	return (0);
}

static char	**extract_clean_command(t_token_list *token_list)
{
	t_token_list	*tmp;
	char			**cmd_args;
	int				count;
	int				i;

	count = count_command_tokens(token_list);
	if (count == 0)
		return (NULL);
	cmd_args = ft_calloc(count + 1, sizeof(char *));
	if (!cmd_args)
		return (NULL);
	tmp = token_list;
	i = 0;
	while (tmp && i < count && tmp->token->type != TOKEN_PIPE)
	{
		if (tmp->token->type == TOKEN_COMMAND || tmp->token->type == TOKEN_WORD)
		{
			cmd_args[i] = ft_strdup(tmp->token->value);
			i++;
			tmp = tmp->next;
		}
		else
			tmp = skip_redirect_token(tmp);
	}
	return (cmd_args);
}

int	execute_redirect_child(t_minishell *minishell)
{
	char	**cmd;
	int		ret;

	cmd = extract_clean_command(minishell->token_list);
	if (!cmd || !cmd[0])
	{
		if (cmd)
			free_double(cmd);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "pwd")
		|| !ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "cd")
		|| !ft_strcmp(cmd[0], "export") || !ft_strcmp(cmd[0], "unset")
		|| !ft_strcmp(cmd[0], "exit"))
		ret = execute_builtin_with_redirect(cmd, minishell);
	else
		ret = execute_external_command(cmd, minishell);
	free_double(cmd);
	return (ret);
}
