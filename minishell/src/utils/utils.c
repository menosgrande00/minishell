/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:00:34 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:11:45 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && (i < n))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	calloc_minishell(t_minishell *minishell)
{
	minishell->count = malloc(sizeof(t_count));
	if (!minishell->count)
	{
		perror("malloc");
		return (1);
	}
	minishell->count->pipe_count = 0;
	minishell->count->redir_in_count = 0;
	minishell->count->redir_out_count = 0;
	minishell->count->append_count = 0;
	minishell->count->heredoc_count = 0;
	return (0);
}

void	reset_counts(t_minishell *minishell)
{
	if (!minishell || !minishell->count)
		return ;
	minishell->count->pipe_count = 0;
	minishell->count->redir_in_count = 0;
	minishell->count->redir_out_count = 0;
	minishell->count->append_count = 0;
	minishell->count->heredoc_count = 0;
}
