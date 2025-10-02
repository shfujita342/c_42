/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:21:26 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:54:52 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_double_quote(const char *str, int *i, char **buffer,
		t_shell *shell)
{
	char	*tmp;

	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			tmp = expand_var(str, i, shell);
			*buffer = str_append_str(*buffer, tmp);
			free(tmp);
		}
		else
		{
			*buffer = str_append_char(*buffer, str[*i]);
			(*i)++;
		}
	}
	if (str[*i] == '"')
		(*i)++;
}

static void	handle_single_quote(const char *str, int *i, char **buffer)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		*buffer = str_append_char(*buffer, str[*i]);
		(*i)++;
	}
	if (str[*i] == '\'')
		(*i)++;
}

void	handle_dollar(const char *str, int *i, char **buffer, t_shell *shell)
{
	char	*tmp;

	tmp = expand_var(str, i, shell);
	*buffer = str_append_str(*buffer, tmp);
	free(tmp);
}

void	handle_normal_char(const char *str, int *i, char **buffer)
{
	*buffer = str_append_char(*buffer, str[*i]);
	(*i)++;
}

char	*expand_env(const char *str, t_shell *shell)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = malloc(1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (str[i])
	{
		if (str[i] == '\'' && is_valid_quote(str, i))
			handle_single_quote(str, &i, &buffer);
		else if (str[i] == '"' && is_valid_quote(str, i))
			handle_double_quote(str, &i, &buffer, shell);
		else if (str[i] == '$')
			handle_dollar(str, &i, &buffer, shell);
		else
			handle_normal_char(str, &i, &buffer);
	}
	return (buffer);
}
