/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:23:20 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quoted_string(const char *str, size_t len)
{
	if (len < 2)
		return (0);
	if (str[0] == '\'' && str[len - 1] == '\'')
		return (1);
	if (str[0] == '\"' && str[len - 1] == '\"')
		return (2);
	return (0);
}

int	count_cmd(char **cmd)
{
	int	count;

	count = 0;
	if (!cmd)
		return (0);
	while (cmd[count] != NULL)
		count++;
	return (count);
}

char	*remove_quotes(const char *str)
{
	size_t	len;
	char	*res;

	len = ft_strlen(str);
	if (len == 0)
		return (ft_strdup(""));
	if (is_quoted_string(str, len))
	{
		res = malloc(len - 1);
		if (!res)
			return (NULL);
		ft_memcpy(res, str + 1, len - 2);
		res[len - 2] = '\0';
		return (res);
	}
	return (ft_strdup(str));
}

char	*remove_quotes_with_flag(const char *str, int *quoted)
{
	size_t	len;
	char	*res;

	len = ft_strlen(str);
	*quoted = 0;
	if (len == 0)
		return (ft_strdup(""));
	if (is_quoted_string(str, len))
	{
		*quoted = 1;
		res = malloc(len - 1);
		if (!res)
			return (NULL);
		ft_memcpy(res, str + 1, len - 2);
		res[len - 2] = '\0';
		return (res);
	}
	return (ft_strdup(str));
}
