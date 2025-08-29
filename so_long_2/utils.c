/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:01:19 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/29 17:11:17 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*p;

	len = ft_strlen(s);
	p = (char *)safe_malloc(len + 1);
	memcpy(p, s, len);
	p[len] = '\0';
	return (p);
}

void	putstr_fd(const char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	*safe_malloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		print_error("malloc");
	return (p);
}

char	**dup_grid(char **grid, int h)
{
	int		i;
	char	**dup;

	dup = (char **)safe_malloc(sizeof(char *) * (h + 1));
	i = 0;
	while (i < h)
	{
		dup[i] = ft_strdup(grid[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
