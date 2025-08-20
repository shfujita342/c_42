/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:05:30 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/19 19:40:54 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env_path(char *envp[])
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*search_cmd_path(char *cmd, char **dir_path)
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
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*resolve_path(char *cmd, char *envp[])
{
	char	*env_path;
	char	**dir_paths;
	char	*res;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	env_path = get_env_path(envp);
	if (!env_path)
		return (NULL);
	dir_paths = ft_split(env_path, ':');
	if (!dir_paths)
		return (NULL);
	res = search_cmd_path(cmd, dir_paths);
	free_strv(dir_paths);
	return (res);
}
