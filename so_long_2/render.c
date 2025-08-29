/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:59:16 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/29 20:55:57 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_tile(t_game *g, void *img, int x, int y)
{
	mlx_put_image_to_window(g->mlx, g->win, img, x * TILE, y * TILE);
}

static void	draw_cell(t_game *g, int x, int y)
{
	char	c;

	c = g->map.grid[y][x];
	put_tile(g, g->tex_floor.ptr, x, y);
	if (c == '1')
		put_tile(g, g->tex_wall.ptr, x, y);
	else if (c == 'C')
		put_tile(g, g->tex_collect.ptr, x, y);
	else if (c == 'E')
		put_tile(g, g->tex_exit.ptr, x, y);
	else if (c == 'P')
		put_tile(g, g->tex_player.ptr, x, y);
}

void	render(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->map.h)
	{
		x = 0;
		while (x < g->map.w)
		{
			draw_cell(g, x, y);
			x++;
		}
		y++;
	}
}
