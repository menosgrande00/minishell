/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_back_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:19:58 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:08:21 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_home(t_minishell *minishell)
{
	char	*home;
	t_env	*env;

	home = NULL;
	env = minishell->envp;
	while (env)
	{
		if (ft_strncmp(env->key, "HOME",
				ft_strlen(env->key) - 1) == 0)
		{
			home = env->value;
			break ;
		}
		env = env->next;
	}
	return (home);
}

static int	check_and_prepare_cd(char *cwd, char **new_path, t_minishell *ms,
		char ***paths)
{
	char	*home;

	*paths = ft_split(cwd, '/');
	if (!*paths)
	{
		free(cwd);
		return (1);
	}
	home = find_home(ms);
	*new_path = ft_strdup("");
	if (!home)
	{
		report_error(ms, "minishell: cd: HOME not set\n", 1);
		free(cwd);
		free_double(*paths);
		free(*new_path);
		return (1);
	}
	if (!ft_strcmp(cwd, home))
	{
		free_double(*paths);
		free(*new_path);
		return (1);
	}
	return (0);
}

static void	build_new_path(char **new_path, char **paths)
{
	int		i;
	char	*temp;

	i = 0;
	while (paths[i + 1])
	{
		temp = ft_strjoin(*new_path, "/");
		free(*new_path);
		*new_path = ft_strjoin(temp, paths[i]);
		free(temp);
		i++;
	}
}

int	ft_cd_back_one(char *cwd, char *new_path, t_minishell *minishell)
{
	char	**paths;

	if (check_and_prepare_cd(cwd, &new_path, minishell, &paths) != 0)
		return (1);
	build_new_path(&new_path, paths);
	free_double(paths);
	free(cwd);
	if (!new_path)
		return (1);
	if (chdir(new_path))
	{
		report_no_such_file(minishell, new_path);
		free(new_path);
		return (1);
	}
	free(new_path);
	return (0);
}
