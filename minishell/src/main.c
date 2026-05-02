/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:58:08 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:04:32 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*create_minishell(void)
{
	t_minishell	*minishell;

	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
	{
		perror("malloc");
		return (NULL);
	}
	if (calloc_minishell(minishell))
	{
		free(minishell);
		return (NULL);
	}
	minishell->input = NULL;
	minishell->envp = NULL;
	minishell->tokens = NULL;
	minishell->token_list = NULL;
	minishell->export = NULL;
	minishell->exit_status = 0;
	return (minishell);
}

void	run_shell(t_minishell *minishell)
{
	while (1)
	{
		init_signal();
		minishell->input = readline("minishell> ");
		if (check_signal() == SIGINT)
			minishell->exit_status = 130;
		if (!minishell->input)
			break ;
		else if (*minishell->input)
		{
			add_history(minishell->input);
			if (tokenizer(minishell))
			{
				parse_tokens(minishell, minishell->token_list);
				if (minishell->token_list)
					execute_command(minishell);
			}
		}
		if (minishell->token_list)
		{
			free_token_list(minishell->token_list);
			minishell->token_list = NULL;
		}
		free(minishell->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell		*minishell;

	(void)argc;
	(void)argv;
	minishell = create_minishell();
	if (!minishell)
		return (1);
	minishell->envp = init_env(envp);
	if (!minishell->envp)
	{
		free_for_exit(minishell);
		return (1);
	}
	run_shell(minishell);
	free_for_exit(minishell);
	return (0);
}
