/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_after_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:25:26 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:10:54 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_to_last_token(t_minishell *minishell, const char *result)
{
	t_token_list	*last;
	char			*combined;

	last = minishell->token_list;
	while (last && last->next)
		last = last->next;
	if (last)
	{
		combined = ft_strjoin(last->token->value, result);
		if (combined)
		{
			free(last->token->value);
			last->token->value = combined;
		}
	}
}

static char	*handle_single_char(const char *input, int *pos_ptr, char *result)
{
	char	*single;
	char	*tmp;

	single = malloc(2);
	if (!single)
	{
		free(result);
		return (NULL);
	}
	single[0] = input[*pos_ptr];
	single[1] = '\0';
	tmp = ft_strjoin(result, single);
	free(result);
	free(single);
	if (!tmp)
		return (NULL);
	*pos_ptr = *pos_ptr + 1;
	return (tmp);
}

static char	*handle_quoted_segment(const char *input, int *pos, char *result)
{
	int		qs;
	int		qe;
	char	*quoted;
	char	*tmp;

	qs = *pos;
	qe = qs + 1;
	while (input[qe] && input[qe] != '"')
		qe++;
	if (input[qe] != '"')
		return (result);
	quoted = ft_substr(input, qs + 1, qe - qs - 1);
	if (!quoted)
		return (result);
	tmp = ft_strjoin(result, quoted);
	free(result);
	free(quoted);
	if (!tmp)
		return (NULL);
	*pos = qe + 1;
	return (tmp);
}

static char	*handle_single_quote(const char *input, int *pos, char *result)
{
	int		qe;
	char	*segment;
	char	*tmp;
	int		k;

	qe = *pos + 1;
	while (input[qe] && input[qe] != '\'')
		qe++;
	if (input[qe] != '\'')
		return (result);
	segment = ft_substr(input, *pos + 1, qe - *pos - 1);
	if (!segment)
		return (result);
	k = -1;
	while (segment[++k])
		if (segment[k] == '$')
			segment[k] = 1;
	tmp = ft_strjoin(result, segment);
	free(result);
	free(segment);
	if (!tmp)
		return (NULL);
	*pos = qe + 1;
	return (tmp);
}

char	*collect_after_quot(const char *input, int start_idx, int *end_pos)
{
	int		pos;
	char	*result;

	pos = start_idx + 1;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (input[pos] && input[pos] != ' ')
	{
		if (input[pos] == '"')
			result = handle_quoted_segment(input, &pos, result);
		else if (input[pos] == '\'')
			result = handle_single_quote(input, &pos, result);
		else
			result = handle_single_char(input, &pos, result);
		if (!result)
			return (NULL);
	}
	*end_pos = pos;
	return (result);
}
