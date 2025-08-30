/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:56:41 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/30 18:42:37 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	open_map_fd(const char *path)
{
	int		fd;
	char	*alt;

	if (!path)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd >= 0)
		return (fd);
	if (!ft_strchr(path, '/'))
	{
		alt = ft_strjoin("maps/", path);
		if (!alt)
			print_error("malloc");
		fd = open(alt, O_RDONLY);
		free(alt);
	}
	return (fd);
}

static char	*read_all_to_acc(int fd)
{
	char	*acc;
	char	*line;

	acc = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (is_blank_line(line))
		{
			free(line);
			free(acc);
			gnl_drain(fd);
			close(fd);
			return (NULL);
		}
		acc = append_line(acc, line, fd);
		free(line);
		line = get_next_line(fd);
	}
	return (acc);
}

char	**read_map_lines(const char *path)
{
	int		fd;
	char	*acc;
	char	**rows;

	fd = open_map_fd(path);
	if (fd < 0)
		return (NULL);
	acc = read_all_to_acc(fd);
	close(fd);
	if (!acc)
		return (NULL);
	rows = ft_split(acc, '\n');
	if (!rows)
	{
		free(acc);
		print_error("malloc");
	}
	free(acc);
	return (rows);
}

int	load_map(const char *path, t_map *m)
{
	ft_memset(m, 0, sizeof(*m));
	m->grid = read_map_lines(path);
	if (!m->grid)
		return (0);
	while (m->grid[m->h])
		m->h++;
	if (m->h > 0)
		m->w = (int)ft_strlen(m->grid[0]);
	return (1);
}
