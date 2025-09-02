/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:59:16 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/31 11:57:42 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_cell(t_game *g, int x, int y)
{
	char	c;

	c = g->map.grid[y][x];
	mlx_put_image_to_window(g->mlx, g->win, g->tex_floor.ptr, x * TILE, y
		* TILE);
	if (c == '1')
		mlx_put_image_to_window(g->mlx, g->win, g->tex_wall.ptr, x * TILE, y
			* TILE);
	else if (c == 'C')
		mlx_put_image_to_window(g->mlx, g->win, g->tex_collect.ptr, x * TILE, y
			* TILE);
	else if (c == 'E')
		mlx_put_image_to_window(g->mlx, g->win, g->tex_exit.ptr, x * TILE, y
			* TILE);
	else if (c == 'P')
		mlx_put_image_to_window(g->mlx, g->win, g->tex_player.ptr, x * TILE, y
			* TILE);
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
