/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:56:41 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/29 16:26:29 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_lines(const char *s)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			c++;
		i++;
	}
	if (i && s[i - 1] != '\n')
		c++;
	return (c);
}

static void	assign_rows(char **rows, char *buf)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (buf[j])
	{
		k = j;
		while (buf[j] && buf[j] != '\n')
			j++;
		rows[i] = (char *)safe_malloc((j - k + 1) * sizeof(char));
		memcpy(rows[i], buf + k, j - k);
		rows[i][j - k] = '\0';
		if (buf[j] == '\n')
			j++;
		i++;
	}
	rows[i] = NULL;
}

char	*read_file(const char *path)
{
	int		fd;
	ssize_t	n;
	char	buf[4096];
	char	*acc;
	char	*tmp;
	size_t	len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	acc = NULL;
	len = 0;
	n = read(fd, buf, 4096);
	while (n > 0)
	{
		tmp = (char *)safe_malloc(len + n + 1);
		if (acc)
			memcpy(tmp, acc, len);
		memcpy(tmp + len, buf, n);
		len += n;
		tmp[len] = '\0';
		free(acc);
		acc = tmp;
		n = read(fd, buf, 4096);
	}
	close(fd);
	return (acc);
}

char	**split_lines(char *buf)
{
	char	**rows;
	int		lines;

	if (!buf)
		return (NULL);
	lines = count_lines(buf);
	if (lines <= 0)
		return (NULL);
	rows = (char **)safe_malloc(sizeof(char *) * (lines + 1));
	assign_rows(rows, buf);
	return (rows);
}

int	load_map(const char *path, t_map *m)
{
	char	*buf;

	memset(m, 0, sizeof(*m));
	buf = read_file(path);
	if (!buf)
		return (0);
	m->grid = split_lines(buf);
	free(buf);
	if (!m->grid)
		return (0);
	while (m->grid[m->h])
		m->h++;
	if (m->h > 0)
		m->w = (int)ft_strlen(m->grid[0]);
	return (1);
}
