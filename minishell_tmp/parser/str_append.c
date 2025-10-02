/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:39:02 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_append_str(char *s, const char *append)
{
	size_t	len_s;
	size_t	len_a;
	char	*new_str;

	len_s = 0;
	if (s != NULL)
		len_s = ft_strlen(s);
	len_a = 0;
	if (append != NULL)
		len_a = ft_strlen(append);
	new_str = malloc(len_s + len_a + 1);
	if (!new_str)
	{
		free(s);
		return (NULL);
	}
	if (s != NULL)
	{
		ft_memcpy(new_str, s, len_s);
		free(s);
	}
	if (append != NULL)
		ft_memcpy(new_str + len_s, append, len_a);
	new_str[len_s + len_a] = '\0';
	return (new_str);
}

char	*str_append_char(char *s, char c)
{
	size_t	len;
	char	*new_str;

	len = 0;
	if (s != NULL)
		len = ft_strlen(s);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(s);
		return (NULL);
	}
	if (s != NULL)
	{
		ft_memcpy(new_str, s, len);
		free(s);
	}
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

char	*str_append_except_for_quotes(char *buff, char *str, int *i)
{
	char	c;
	int		start;
	char	*tmp;

	c = str[*i];
	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != c)
		(*i)++;
	tmp = ft_strndup(str + start, *i - start);
	buff = str_append_str(buff, tmp);
	free(tmp);
	return (buff);
}
