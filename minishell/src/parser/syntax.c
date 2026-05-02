/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:35:24 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:11:16 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_tmp_envp(char *tmp, int *dollar_idx, char *value, int key_len)
{
	int		end;
	int		new_len;
	char	*out;
	int		i;
	int		k;

	end = *dollar_idx + 1 + key_len;
	new_len = *dollar_idx + ft_strlen(value) + ft_strlen(&tmp[end]);
	out = malloc(new_len + 1);
	if (!out)
		return (NULL);
	i = -1;
	while (++i < *dollar_idx)
		out[i] = tmp[i];
	k = 0;
	while (value[k])
		out[i++] = value[k++];
	k = end;
	while (tmp[k])
		out[i++] = tmp[k++];
	out[i] = '\0';
	return (out);
}

char	*env_expand(t_minishell *minishell, char *tmp, int *j)
{
	char	*key;
	char	*value;
	char	*new_tmp;
	int		dollar;
	size_t	val_len;

	dollar = *j;
	(*j)++;
	key = extract_env_key(tmp, j);
	if (!key)
	{
		*j = dollar;
		return (ft_strdup(tmp));
	}
	value = get_env_value(minishell->envp, key);
	if (!value)
		value = "";
	val_len = ft_strlen(value);
	new_tmp = replace_tmp_envp(tmp, &dollar, value, (int)ft_strlen(key));
	free(key);
	if (!new_tmp)
		return (NULL);
	*j = dollar + (int)val_len - 1;
	return (new_tmp);
}

static int	money_money_process(t_minishell *minishell, char **tmp, int *j)
{
	char	*status;
	char	*new_tmp;
	int		dollar;
	size_t	val_len;

	status = ft_itoa(minishell->exit_status);
	if (!status)
		return (1);
	val_len = ft_strlen(status);
	dollar = *j;
	new_tmp = replace_tmp_envp(*tmp, &dollar, status, 1);
	free(status);
	if (!new_tmp)
		return (1);
	free(*tmp);
	*tmp = new_tmp;
	*j = dollar + (int)val_len - 1;
	return (0);
}

static int	money_expand(t_minishell *minishell, char **tmp)
{
	int		j;
	char	*new_tmp;

	j = -1;
	while ((*tmp)[++j])
	{
		if ((*tmp)[j] == '$')
		{
			if ((*tmp)[j + 1] == '?')
			{
				if (money_money_process(minishell, tmp, &j))
					return (1);
			}
			else if ((*tmp)[j + 1])
			{
				new_tmp = env_expand(minishell, *tmp, &j);
				if (!new_tmp)
					return (1);
				free(*tmp);
				*tmp = new_tmp;
			}
		}
	}
	return (0);
}

int	money_money(t_minishell *minishell, char **tmp)
{
	int	j;

	if (money_expand(minishell, tmp))
		return (1);
	j = -1;
	while ((*tmp)[++j])
		if ((*tmp)[j] == 1)
			(*tmp)[j] = '$';
	return (0);
}
