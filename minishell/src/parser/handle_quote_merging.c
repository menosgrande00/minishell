/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote_merging.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:51:37 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:01:42 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rebuild_input_update_index(t_minishell *minishell,
	t_rebuild_info info, int *index)
{
	int		rem_len;
	int		total_len;
	char	*new_input;
	int		i;
	int		j;

	rem_len = ft_strlen(&minishell->input[info.start]);
	total_len = info.prefix_len + rem_len;
	new_input = malloc(total_len + 1);
	i = 0;
	if (!new_input)
		return (1);
	i = -1;
	while (++i < info.prefix_len)
		new_input[i] = minishell->input[i];
	j = -1;
	while (++j < rem_len)
		new_input[info.prefix_len + j] = minishell->input[info.start + j];
	new_input[total_len] = '\0';
	free(minishell->input);
	minishell->input = new_input;
	*index = info.prefix_len - 1;
	return (0);
}

int	handle_after_quote_text(t_minishell *minishell, int *i, int j)
{
	char			*result;
	t_token_list	*last;
	t_rebuild_info	info;

	result = collect_after_quot(minishell->input, *i, &info.start);
	if (!result)
		return (1);
	if (money_money(minishell, &result))
	{
		free(result);
		return (1);
	}
	append_to_last_token(minishell, result);
	last = minishell->token_list;
	while (last && last->next)
		last = last->next;
	if (last)
		info.new_token_len = ft_strlen(last->token->value);
	else
		info.new_token_len = 0;
	free(result);
	info.prefix_len = j;
	minishell->exit_status = rebuild_input_update_index(minishell, info, i);
	return (minishell->exit_status);
}

int	is_redirection(char *value)
{
	int	i;

	i = 0;
	if (!ft_strcmp(value, ">")
		|| !ft_strcmp(value, "<")
		|| !ft_strcmp(value, ">>")
		|| !ft_strcmp(value, "<<"))
		i = 1;
	return (i);
}

int	merge_with_previous_token(t_minishell *minishell, t_token **current_token)
{
	t_token_list	*last;
	char			*new_value;

	last = minishell->token_list;
	while (last && last->next)
		last = last->next;
	if (last && (*current_token)->value && last->prev && last->prev->token)
	{
		if (is_redirection(last->token->value))
		{
			add_token_to_list(&minishell->token_list, *current_token);
			return (0);
		}
		new_value = ft_strjoin(last->token->value, (*current_token)->value);
		if (new_value)
		{
			free(last->token->value);
			last->token->value = new_value;
			free((*current_token)->value);
			free(*current_token);
		}
	}
	else
		add_token_to_list(&minishell->token_list, *current_token);
	return (0);
}

void	remove_quotes_from_input(t_minishell *ms, int j_pos, int i_pos, char q)
{
	char	*new_input;
	int		k;
	int		x;

	new_input = malloc((ft_strlen(ms->input)) - 1);
	if (!new_input)
		return ;
	k = 0;
	x = 0;
	while (x < j_pos)
		new_input[k++] = ms->input[x++];
	x = j_pos;
	while (++x < i_pos)
	{
		if (q == '\'' && ms->input[x] == '$')
			new_input[k++] = 1;
		else
			new_input[k++] = ms->input[x];
	}
	x = i_pos + 1;
	while (x < (int)(ft_strlen(ms->input)))
		new_input[k++] = ms->input[x++];
	new_input[k] = '\0';
	free(ms->input);
	ms->input = new_input;
}
