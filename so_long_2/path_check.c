/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:58:48 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/30 21:10:23 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood(t_fctx *c, int x, int y)
{
	if (x < 0 || y < 0 || x >= c->w || y >= c->h)
		return ;
	if (c->g[y][x] == '1' || c->g[y][x] == 'V')
		return ;
	if (c->block_exit && c->g[y][x] == 'E')
		return ;
	c->g[y][x] = 'V';
	flood(c, x + 1, y);
	flood(c, x - 1, y);
	flood(c, x, y + 1);
	flood(c, x, y - 1);
}

static int	all_c_reached(t_fctx *c)
{
	int	y;
	int	x;

	y = 0;
	while (y < c->h)
	{
		x = 0;
		while (x < c->w)
		{
			if (c->g[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	exit_adjacent_reachable(t_fctx *c, char **orig)
{
	int	y;
	int	x;

	y = 0;
	while (y < c->h)
	{
		x = 0;
		while (x < c->w)
		{
			if (orig[y][x] == 'E')
			{
				if ((y > 0 && c->g[y - 1][x] == 'V') || (y + 1 < c->h && c->g[y
						+ 1][x] == 'V') || (x > 0 && c->g[y][x - 1] == 'V')
					|| (x + 1 < c->w && c->g[y][x + 1] == 'V'))
					return (1);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_path(t_map *m)
{
	char	**g;
	t_fctx	c;

	g = dup_grid(m->grid, m->h);
	if (!g)
		return (0);
	c.g = g;
	c.w = m->w;
	c.h = m->h;
	c.block_exit = 1;
	g[m->p_y][m->p_x] = '0';
	flood(&c, m->p_x, m->p_y);
	if (!all_c_reached(&c) || !exit_adjacent_reachable(&c, m->grid))
	{
		free_grid(g, m->h);
		return (0);
	}
	free_grid(g, m->h);
	return (1);
}
