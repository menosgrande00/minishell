/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_in_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:52:13 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:10:43 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	re_build_input(t_minishell *ms, int *i, char *value, int key_len)
{
	char	*last;
	char	*new_input;
	int		new_total_len;

	new_total_len = (*i) + ft_strlen(value)
		+ ft_strlen(&ms->input[(*i) + key_len + 1]);
	last = malloc(ft_strlen(&ms->input[(*i) + key_len + 1]) + 1);
	if (!last)
		return (1);
	ft_strcpy(last, &ms->input[(*i) + key_len + 1]);
	new_input = malloc(new_total_len + 1);
	if (!new_input)
	{
		free(last);
		return (1);
	}
	ft_strncpy(new_input, ms->input, (*i));
	ft_strcpy(new_input + (*i), value);
	ft_strcpy(new_input + (*i) + ft_strlen(value), last);
	new_input[new_total_len] = '\0';
	free(ms->input);
	ms->input = new_input;
	free(last);
	(*i) += ft_strlen(value);
	return (0);
}

static int	set_input_path(t_minishell *minishell, int *i)
{
	char	*key;
	char	*value;
	int		len;

	key = extract_env_key_double(minishell, i);
	if (!key)
		return (1);
	value = get_env_value(minishell->envp, key);
	len = ft_strlen(key);
	free(key);
	if (!value)
		value = "";
	if (re_build_input(minishell, i, value, len))
		return (1);
	return (0);
}

static char	*prepare_remaining_input(t_minishell *minishell, int start_pos)
{
	char	*last;
	int		total_len;
	int		copy_start;
	int		j;

	total_len = start_pos;
	while (minishell->input[total_len])
		total_len++;
	last = malloc(total_len - 2);
	if (!last)
		return (NULL);
	j = 0;
	copy_start = start_pos + 2;
	while (minishell->input[copy_start])
		last[j++] = minishell->input[copy_start++];
	last[j] = '\0';
	return (last);
}

static int	replace_input(t_minishell *minishell, int *i)
{
	char	*status;
	char	*last;
	int		len;
	int		j;

	status = ft_itoa(minishell->exit_status);
	last = prepare_remaining_input(minishell, *i);
	if (!last)
		return (1);
	j = 0;
	len = *i;
	while (status[j])
		minishell->input[len++] = status[j++];
	free(status);
	(*i) += j;
	j = 0;
	while (last[j])
		minishell->input[len++] = last[j++];
	minishell->input[len] = '\0';
	free(last);
	return (0);
}

int	handle_dollar_in_quotes(t_minishell *minishell, int *i, int *start)
{
	(void)start;
	if (minishell->input[*i] == '$' && minishell->input[*i + 1] == '"')
	{
		(*i)++;
		return (0);
	}
	else if (minishell->input[*i] == '$' && minishell->input[*i + 1] == '?')
	{
		if (replace_input(minishell, i))
			return (-1);
	}
	else if (minishell->input[*i] == '$')
	{
		if (set_input_path(minishell, i))
			return (-1);
	}
	return (0);
}
