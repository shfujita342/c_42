/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:54:11 by shfujita          #+#    #+#             */
/*   Updated: 2025/09/19 13:44:15 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_strv(char **strv)
{
	int	i;

	if (!strv)
		return ;
	i = 0;
	while (strv[i])
	{
		free(strv[i]);
		i++;
	}
	free(strv);
}

static int	is_executable_file(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (0);
	if (access(path, F_OK) != 0)
		return (0);
	return (1);
}

static char	*get_env_path(t_env *env_list)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->key, "PATH", 4) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

static char	*search_cmd_path(char *cmd, char **dir_path)
{
	int		i;
	char	*full_path;
	char	*tmp;
	char	*dir;

	i = 0;
	while (dir_path[i])
	{
		dir = dir_path[i];
		if (dir_path[i][0] == '\0')
			dir = ".";
		tmp = ft_strjoin(dir, "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			break ;
		if (is_executable_file(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*resolve_path(char *cmd, t_env *env_list)
{
	char	*env_path;
	char	**dir_paths;
	char	*res;

	if (ft_strchr(cmd, '/'))
	{
		if (is_executable_file(cmd))
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	env_path = get_env_path(env_list);
	if (!env_path)
		return (NULL);
	dir_paths = ft_split(env_path, ':');
	if (!dir_paths)
		return (NULL);
	res = search_cmd_path(cmd, dir_paths);
	free_strv(dir_paths);
	return (res);
}
