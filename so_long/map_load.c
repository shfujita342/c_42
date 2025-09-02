/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:56:41 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/31 11:55:30 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*append_line(char *accum, char *line, int fd)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(line);
	if (!accum)
	{
		accum = ft_strdup(line);
		if (!accum)
		{
			free(line);
			close(fd);
			print_error("malloc");
		}
		return (accum);
	}
	tmp = ft_strjoin(accum, line);
	if (!tmp)
	{
		free(line);
		free(accum);
		close(fd);
		print_error("malloc");
	}
	free(accum);
	return (tmp);
}

int	is_blank_line(const char *s)
{
	if (!s || !s[0])
		return (1);
	if (s[0] == '\n' && s[1] == '\0')
		return (1);
	return (0);
}

static char	*read_all_to_accum(int fd)
{
	char	*accum;
	char	*line;

	accum = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (is_blank_line(line))
		{
			free(line);
			free(accum);
			gnl_drain(fd);
			close(fd);
			return (NULL);
		}
		accum = append_line(accum, line, fd);
		free(line);
		line = get_next_line(fd);
	}
	return (accum);
}

char	**read_map_lines(const char *path)
{
	int		fd;
	char	*tmp;
	char	**rows;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	tmp = read_all_to_accum(fd);
	close(fd);
	if (!tmp)
		return (NULL);
	rows = ft_split(tmp, '\n');
	if (!rows)
	{
		free(tmp);
		print_error("malloc");
	}
	free(tmp);
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
