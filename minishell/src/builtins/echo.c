/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:23:08 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:08:33 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char *tok, int i)
{
	int	no_newline;
	int	j;

	no_newline = 0;
	while (tok[i] == '-' && tok[i + 1] == 'n')
	{
		j = i + 2;
		while (tok[j] == 'n')
			j++;
		if (tok[j] == ' ' || tok[j] == '\t' || tok[j] == '\0')
		{
			no_newline = 1;
			i = j;
			while (tok[i] == ' ' || tok[i] == '\t')
				i++;
		}
		else
			break ;
	}
	while (tok[i])
		write(1, &tok[i++], 1);
	if (!no_newline)
		write(1, "\n", 1);
	return (0);
}

static int	append_to_current(char **current, const char *to_add)
{
	char	*temp;

	temp = ft_strjoin(*current, to_add);
	if (!temp)
	{
		free(*current);
		return (1);
	}
	free(*current);
	*current = temp;
	return (0);
}

static char	*build_echo_string(t_token_list **tmp)
{
	char	*current;
	int		first;

	current = ft_strdup("");
	if (!current)
		return (NULL);
	first = 1;
	while (*tmp && (*tmp)->token->type == TOKEN_WORD)
	{
		if (!first)
		{
			if (append_to_current(&current, " "))
				return (NULL);
		}
		if ((*tmp)->token->value)
		{
			if (append_to_current(&current, (*tmp)->token->value))
				return (NULL);
		}
		*tmp = (*tmp)->next;
		first = 0;
	}
	return (current);
}

int	process_for_echo(t_token_list **tmp)
{
	char	*current;
	int		return_value;
	int		i;

	i = 0;
	*tmp = (*tmp)->next;
	current = build_echo_string(tmp);
	if (!current)
		return (1);
	return_value = ft_echo(current, i);
	free(current);
	return (return_value);
}
