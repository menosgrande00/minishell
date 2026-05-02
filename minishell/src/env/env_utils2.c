/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:35:06 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:09:17 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_and_parse_env(char *arg, char **key, char **value)
{
	char	*eq;

	if (!arg)
		return (0);
	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*key = ft_substr(arg, 0, eq - arg + 1);
		*value = ft_strdup(eq + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = ft_strdup("");
	}
	if (!is_valid_identifier(*key))
	{
		write(2, "minishell: export: `", 20);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		free(*key);
		free(*value);
		return (1);
	}
	return (0);
}

static t_env	*find_existing_env(t_env *envp, char *key)
{
	t_env	*it;

	it = envp;
	while (it)
	{
		if (ft_strlen(it->key) > 1)
		{
			if (!ft_strncmp(it->key, key, ft_strlen(it->key) - 1))
				return (it);
		}
		else if (ft_strlen(it->key) == 1)
		{
			if (!ft_strncmp(it->key, key, ft_strlen(it->key)))
				return (it);
		}
		it = it->next;
	}
	return (NULL);
}

static void	add_new_env_node(t_minishell *minishell, char *key, char *value)
{
	t_env	*it;
	t_env	*last;

	it = ft_calloc(1, sizeof(*it));
	it->key = key;
	it->value = value;
	it->next = NULL;
	if (!minishell->envp)
		minishell->envp = it;
	else
	{
		last = minishell->envp;
		while (last->next)
			last = last->next;
		last->next = it;
	}
}

int	add_env(t_minishell *minishell, char *arg)
{
	char	*key;
	char	*value;
	t_env	*existing;
	int		ret;

	ret = validate_and_parse_env(arg, &key, &value);
	if (ret == 1)
	{
		minishell->exit_status = 1;
		return (1);
	}
	if (ret == 0 && !key)
		return (0);
	existing = find_existing_env(minishell->envp, key);
	if (existing)
	{
		free(existing->value);
		existing->value = value;
		free(key);
		return (0);
	}
	add_new_env_node(minishell, key, value);
	return (0);
}
