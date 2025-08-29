/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:58:48 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/29 22:19:26 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "so_long.h"

// static void	flood(char **g, int w, int h, int x, int y)
// {
// 	if (x < 0 || y < 0)
// 		return ;
// 	if (x >= w || y >= h)
// 		return ;
// 	if (g[y][x] == '1' || g[y][x] == 'V')
// 		return ;
// 	g[y][x] = 'V';
// 	flood(g, w, h, x + 1, y);
// 	flood(g, w, h, x - 1, y);
// 	flood(g, w, h, x, y + 1);
// 	flood(g, w, h, x, y - 1);
// }

// static int	all_reached(char **g, int w, int h)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (y < h)
// 	{
// 		x = 0;
// 		while (x < w)
// 		{
// 			if (g[y][x] == 'C' || g[y][x] == 'E')
// 				return (0);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (1);
// }

// int	check_path(t_map *m)
// {
// 	char	**g;

// 	g = dup_grid(m->grid, m->h);
// 	if (!g)
// 		return (0);
// 	g[m->p_y][m->p_x] = '0';
// 	flood(g, m->w, m->h, m->p_x, m->p_y);
// 	if (!all_reached(g, m->w, m->h))
// 	{
// 		free_grid(g, m->h);
// 		return (0);
// 	}
// 	free_grid(g, m->h);
// 	return (1);
// }

#include "so_long.h"

static void	flood(char **g, int w, int h, int x, int y, int block_exit)
{
	if (x < 0 || y < 0 || x >= w || y >= h)
		return ;
	if (g[y][x] == '1' || g[y][x] == 'V')
		return ;
	if (block_exit && g[y][x] == 'E')
		return ;
	g[y][x] = 'V';
	flood(g, w, h, x + 1, y, block_exit);
	flood(g, w, h, x - 1, y, block_exit);
	flood(g, w, h, x, y + 1, block_exit);
	flood(g, w, h, x, y - 1, block_exit);
}

static int	all_c_reached(char **g, int w, int h)
{
	int	y;
	int	x;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (g[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	exit_adjacent_reachable(char **visited, char **orig, int w, int h)
{
	int	y;
	int	x;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (orig[y][x] == 'E')
			{
				if ((y > 0 && visited[y - 1][x] == 'V') || (y + 1 < h
						&& visited[y + 1][x] == 'V') || (x > 0 && visited[y][x
						- 1] == 'V') || (x + 1 < w && visited[y][x + 1] == 'V'))
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

	g = dup_grid(m->grid, m->h);
	if (!g)
		return (0);
	g[m->p_y][m->p_x] = '0';
	flood(g, m->w, m->h, m->p_x, m->p_y, 1); /* E を壁扱い */
	if (!all_c_reached(g, m->w, m->h) || !exit_adjacent_reachable(g, m->grid,
			m->w, m->h))
	{
		free_grid(g, m->h);
		return (0);
	}
	free_grid(g, m->h);
	return (1);
}
