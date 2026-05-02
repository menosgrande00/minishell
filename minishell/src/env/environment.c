/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:35:27 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:09:25 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static char	*create_env_key(char *str, char *eq)
{
	char	*key;
	int		i;

	i = ft_strlen(str) - ft_strlen(eq);
	key = ft_substr(str, 0, i + 1);
	return (key);
}

t_env	*env_node(char *str)
{
	t_env	*node;
	char	*eq;

	eq = ft_strchr(str, '=');
	if (!eq || !str)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = create_env_key(str, eq);
	if (!(node->key))
	{
		free(node);
		return (NULL);
	}
	node->value = ft_strdup(eq + 1);
	if (!(node->value))
	{
		free(node->key);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

static void	add_env_node(t_env **first, t_env **last, t_env *node)
{
	if (!node)
		return ;
	if (*first == NULL)
	{
		*first = node;
		*last = node;
	}
	else
	{
		(*last)->next = node;
		*last = node;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*first;
	t_env	*last;
	t_env	*node;
	int		i;

	first = NULL;
	last = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		node = env_node(envp[i]);
		if (!node)
		{
			free_env_list(first);
			return (NULL);
		}
		add_env_node(&first, &last, node);
		i++;
	}
	return (first);
}
