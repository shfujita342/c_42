/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:02:05 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/29 15:02:16 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_pos(long n, int fd)
{
	char	c;

	if (n >= 10)
		put_pos(n / 10, fd);
	c = (char)('0' + (n % 10));
	write(fd, &c, 1);
}

void	putnbr_fd(int n, int fd)
{
	long	v;

	v = n;
	if (v < 0)
	{
		write(fd, "-", 1);
		v = -v;
	}
	put_pos(v, fd);
}

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
