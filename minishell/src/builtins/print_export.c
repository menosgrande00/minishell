/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:30:31 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:08:52 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		env = env->next;
		size++;
	}
	return (size);
}

static t_env	**env_to_array(t_env *env)
{
	int		i;
	int		size;
	t_env	**arr;

	i = 0;
	size = env_size(env);
	arr = malloc(sizeof(t_env *) * (size + 1));
	if (!arr)
		return (NULL);
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	sort_env_array(t_env **arr)
{
	int		i;
	int		j;
	int		size;
	t_env	*temp;

	i = 0;
	size = 0;
	while (arr[size])
		size++;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1)
		{
			if (ft_strncmp(arr[j]->key, arr[j + 1]->key, 1000) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_envs_alphabetic(t_env *env)
{
	t_env	**arr;
	int		i;
	int		len;

	i = 0;
	arr = env_to_array(env);
	if (!arr)
		return ;
	sort_env_array(arr);
	while (arr[i])
	{
		len = ft_strlen(arr[i]->key);
		printf("declare -x %s", arr[i]->key);
		if (arr[i]->value)
			printf("%s", arr[i]->value);
		if ((!arr[i]->value || *arr[i]->value == '\0')
			&& arr[i]->key[len - 1] == '=')
			printf("\"\"");
		printf("\n");
		i++;
	}
	free(arr);
}
