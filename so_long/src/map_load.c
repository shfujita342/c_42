/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:56:41 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/31 11:32:54 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*append_line(char *acc, char *line, int fd)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(line);
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

	fd = open(path, O_RDONLY);
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
