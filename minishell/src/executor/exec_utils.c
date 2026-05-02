/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:43:14 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/13 17:22:59 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_valid_identifier(const char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (name[i] == '=')
		{
			i++;
			continue ;
		}
		else if ((!ft_isalnum(name[i]) && name[i] != '_')
			|| (!ft_isalnum(name[i]) && name[i] != '\0'))
			return (0);
		i++;
	}
	return (1);
}

int	same_token_number(t_token_list **tmp)
{
	int				count;
	t_token_list	*last;

	last = *tmp;
	count = 0;
	while (last && (last->token->type == TOKEN_COMMAND
			|| last->token->type == TOKEN_WORD))
	{
		count++;
		last = last->next;
	}
	return (count);
}

char	**ft_same_tokens(t_token_list **tmp)
{
	int				count;
	char			**tokens;
	int				i;

	i = 0;
	count = same_token_number(tmp);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	while (*tmp && ((*tmp)->token->type == TOKEN_COMMAND
			|| (*tmp)->token->type == TOKEN_WORD))
	{
		tokens[i++] = ft_strdup((*tmp)->token->value);
		*tmp = (*tmp)->next;
	}
	tokens[i] = NULL;
	return (tokens);
}

char	**current_token(t_token_list *tmp)
{
	char	**current_token;

	current_token = malloc(sizeof(char *) * 2);
	if (!current_token)
		return (NULL);
	current_token[0] = tmp->token->value;
	current_token[1] = NULL;
	return (current_token);
}

int	is_dot(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[0][0] == '/')
		return (1);
	while (cmd[0][i] && cmd[0][i] == '.')
	{
		if (cmd[0][i + 1] && cmd[0][i + 1] == '/')
			return (1);
		i++;
	}
	return (0);
}
