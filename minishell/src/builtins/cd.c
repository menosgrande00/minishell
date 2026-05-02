/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:21:20 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:08:25 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_token_with_spaces(t_minishell *minishell)
{
	char	*input;
	char	*trimmed_input;
	int		i;

	i = ft_strlen(minishell->input);
	input = ft_strdup(ft_strnstr(minishell->input, "cd", i) + 2);
	trimmed_input = input;
	while (*trimmed_input == ' ' || *trimmed_input == '\t')
		trimmed_input++;
	return (trimmed_input);
}

static int	ft_go_path(char *cwd, char *new_path, char *current_token)
{
	free(cwd);
	new_path = ft_strdup(current_token);
	if (!new_path)
		return (1);
	if (chdir(new_path))
	{
		write(2, "minishell: cd: ", 15);
		write(2, new_path, ft_strlen(new_path));
		write(2, ": No such file or directory\n", 28);
		free(new_path);
		return (1);
	}
	free(new_path);
	return (0);
}

int	ft_cd_util(char *current_token, char *cwd, char *new_path, t_minishell *ms)
{
	int	ret;

	ret = 0;
	if (current_token[0] == '/')
		ret = ft_go_path(cwd, new_path, current_token);
	else if (!ft_strcmp(current_token, ".."))
		ret = ft_cd_back_one(cwd, new_path, ms);
	else if (!ft_strcmp(current_token, "."))
		free(cwd);
	else
	{
		current_token = ft_token_with_spaces(ms);
		if (chdir(current_token))
		{
			if (errno == EACCES)
				report_perm_denied(ms, current_token);
			else
				report_no_such_file(ms, current_token);
			free(cwd);
			return (1);
		}
		free(cwd);
		free(current_token);
	}
	return (ret);
}

void	ft_cd_back_start(t_minishell *minishell)
{
	t_env	*env;
	char	*home;

	env = minishell->envp;
	home = NULL;
	while (env)
	{
		if (ft_strncmp(env->key, "HOME", ft_strlen(env->key) - 1) == 0)
		{
			home = env->value;
			break ;
		}
		env = env->next;
	}
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return ;
	}
	if (chdir(home))
		perror("minishell: cd");
}

int	ft_cd(t_minishell *minishell)
{
	char			*new_path;
	char			*cwd;
	int				result;
	t_token_list	*tmp;

	cwd = getcwd(NULL, 0);
	new_path = NULL;
	tmp = minishell->token_list;
	if (tmp->next->next)
	{
		free(cwd);
		return (report_error(minishell,
				"minishell: cd: too many arguments", 1));
	}
	if (!tmp->next)
	{
		ft_cd_back_start(minishell);
		return (0);
	}
	result = ft_cd_util(tmp->next->token->value, cwd, new_path, minishell);
	if (result != 0)
		return (1);
	else
		return (0);
}
