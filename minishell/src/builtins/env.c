/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:23:34 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:08:37 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->envp;
	while (tmp)
	{
		if (ft_strchr(tmp->key, '='))
		{
			printf("%s", tmp->key);
			printf("%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
	return (0);
}
