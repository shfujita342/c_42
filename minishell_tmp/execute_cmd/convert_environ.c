/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_environ.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:28:32 by shfujita          #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**write_to_environ(t_env *env, char **environ)
{
	size_t	key_len;
	size_t	value_len;
	size_t	i;
	t_env	*cur;

	cur = env;
	i = 0;
	while (cur)
	{
		key_len = ft_strlen(cur->key);
		value_len = ft_strlen(cur->value);
		environ[i] = malloc(key_len + 1 + value_len + 1);
		if (!environ[i])
			return (NULL);
		ft_strlcpy(environ[i], cur->key, key_len + 1);
		environ[i][key_len] = '=';
		ft_strlcpy(environ[i] + key_len + 1, cur->value, value_len + 1);
		environ[i][key_len + 1 + value_len] = '\0';
		i++;
		cur = cur->next;
	}
	environ[i] = NULL;
	return (environ);
}

char	**convert_env_to_environ(t_env *env)
{
	char	**environ;
	size_t	len;
	t_env	*cur;

	cur = env;
	len = 0;
	while (cur)
	{
		len++;
		cur = cur->next;
	}
	environ = malloc(sizeof(char *) * (len + 1));
	if (!environ)
		return (NULL);
	environ = write_to_environ(env, environ);
	return (environ);
}
