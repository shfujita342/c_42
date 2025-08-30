/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:02:05 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/30 18:33:48 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static void	put_pos(long n, int fd)
// {
// 	char	c;

// 	if (n >= 10)
// 		put_pos(n / 10, fd);
// 	c = (char)('0' + (n % 10));
// 	write(fd, &c, 1);
// }

void	free_grid(char **grid, int h)
{
	int	i;

	i = 0;
	while (i < h)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	free_map(t_map *m)
{
	if (m && m->grid)
		free_grid(m->grid, m->h);
	memset(m, 0, sizeof(*m));
}

char	*append_line(char *acc, char *line, int fd)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(line);
	if (len >= 2 && line[len - 2] == '\r' && line[len - 1] == '\n')
	{
		line[len - 2] = '\n';
		line[len - 1] = '\0';
	}
	else if (len >= 1 && line[len - 1] == '\r')
		line[len - 1] = '\0';
	if (!acc)
	{
		acc = ft_strdup(line);
		if (!acc)
		{
			free(line);
			close(fd);
			print_error("malloc");
		}
		return (acc);
	}
	tmp = ft_strjoin(acc, line);
	if (!tmp)
	{
		free(line);
		free(acc);
		close(fd);
		print_error("malloc");
	}
	free(acc);
	return (tmp);
}

/* 空行: "\n" または "\r\n" のみを true */
int	is_blank_line(const char *s)
{
	if (!s || !s[0])
		return (1);
	if (s[0] == '\n' && s[1] == '\0')
		return (1);
	if (s[0] == '\r' && s[1] == '\n' && s[2] == '\0')
		return (1);
	return (0);
}
