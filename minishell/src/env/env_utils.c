/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:34:19 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:09:12 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_env_array(t_minishell *minishell)
{
	char	**env_array;
	t_env	*tmp;
	int		i;
	int		size;

	size = 0;
	tmp = minishell->envp;
	while (tmp && ++size)
		tmp = tmp->next;
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	tmp = minishell->envp;
	while (tmp)
	{
		env_array[i] = ft_strjoin(tmp->key, tmp->value);
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	*extract_env_key_double(t_minishell *minishell, int *i)
{
	char	*key;
	int		j;
	int		k;

	j = *i + 1;
	k = 0;
	while (minishell->input[j] && minishell->input[j] != ' '
		&& minishell->input[j] != '"')
	{
		j++;
		k++;
	}
	key = malloc(sizeof(char) * k + 1);
	j = *i + 1;
	k = 0;
	while (minishell->input[j] && minishell->input[j] != ' '
		&& minishell->input[j] != '"')
	{
		key[k] = minishell->input[j];
		j++;
		k++;
	}
	key[k] = '\0';
	return (key);
}

char	*extract_env_key(char *tmp, int *j)
{
	char	*key;
	int		start;
	int		len;
	int		i;

	i = *j;
	start = *j;
	while (tmp[i] && (ft_isalnum(tmp[i])
			|| tmp[i] == '_'))
		(i)++;
	len = i - start;
	if (len == 0)
		return (NULL);
	key = ft_substr(tmp, start, len);
	return (key);
}

char	*get_env_value(t_env *envp, char *key)
{
	while (envp)
	{
		if (ft_strncmp(envp->key, key, ft_strlen(envp->key) - 1) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}
