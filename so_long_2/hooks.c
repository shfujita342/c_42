/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:59:55 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/29 15:00:33 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_moves(int mv)
{
	putstr_fd("moves: ", 1);
	putnbr_fd(mv, 1);
	putstr_fd("\n", 1);
}

static int	can_step(t_game *g, int nx, int ny)
{
	char	t;

	if (nx < 0 || ny < 0)
		return (0);
	if (nx >= g->map.w || ny >= g->map.h)
		return (0);
	t = g->map.grid[ny][nx];
	if (t == '1')
		return (0);
	if (t == 'E' && g->collected < g->need)
		return (0);
	return (1);
}

static void	step_to(t_game *g, int nx, int ny)
{
	char	t;

	t = g->map.grid[ny][nx];
	if (t == 'C')
		g->collected++;
	if (t == 'E')
		on_close(g);
	g->map.grid[g->map.p_y][g->map.p_x] = '0';
	g->map.p_x = nx;
	g->map.p_y = ny;
	g->map.grid[ny][nx] = 'P';
	g->moves++;
	print_moves(g->moves);
	render(g);
}

int	on_key(int key, t_game *g)
{
	int	nx;
	int	ny;

	nx = g->map.p_x;
	ny = g->map.p_y;
	if (key == KEY_ESC)
		on_close(g);
	else if (key == KEY_W || key == KEY_UP)
		ny--;
	else if (key == KEY_S || key == KEY_DOWN)
		ny++;
	else if (key == KEY_A || key == KEY_LEFT)
		nx--;
	else if (key == KEY_D || key == KEY_RIGHT)
		nx++;
	if (can_step(g, nx, ny))
		step_to(g, nx, ny);
	return (0);
}

int	on_close(t_game *g)
{
	free_images(g);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	free_map(&g->map);
	exit(0);
	return (0);
}
