/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:25:40 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*expand_var(const char *str, int *i, t_shell *shell)
{
	char	key[256];
	int		k;
	char	*val;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->last_status));
	}
	k = 0;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		key[k++] = str[(*i)++];
	key[k] = '\0';
	if (k == 0)
		return (ft_strdup("$"));
	val = get_env_value(shell->env_list, key);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}
