/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:17:11 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **argv, t_env *envlist)
{
	char	*dir;
	char	*oldpwd;
	char	cwd[4096];

	if (!getcwd(cwd, sizeof(cwd)))
		perror("getcwd");
	oldpwd = ft_strdup(cwd);
	if (!argv[1])
		dir = get_env_value(envlist, "HOME");
	else if (!strcmp(argv[1], "-"))
		dir = get_env_value("OLDPWD");
	else
		dir = argv[1];
}
