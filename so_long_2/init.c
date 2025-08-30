/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:56:05 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/30 15:43:03 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static void	is_ber_file(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		print_error("map extension");
	if (path[len - 4] != '.' || path[len - 3] != 'b' || path[len - 2] != 'e'
		|| path[len - 1] != 'r')
		print_error("map extension");
}

void	load_textures(t_game *g)
{
	g->tex_wall.ptr = mlx_xpm_file_to_image(g->mlx, "textures/wall.xpm",
			&g->tex_wall.w, &g->tex_wall.h);
	g->tex_floor.ptr = mlx_xpm_file_to_image(g->mlx, "textures/floor.xpm",
			&g->tex_floor.w, &g->tex_floor.h);
	g->tex_player.ptr = mlx_xpm_file_to_image(g->mlx, "textures/player.xpm",
			&g->tex_player.w, &g->tex_player.h);
	g->tex_exit.ptr = mlx_xpm_file_to_image(g->mlx, "textures/exit.xpm",
			&g->tex_exit.w, &g->tex_exit.h);
	g->tex_collect.ptr = mlx_xpm_file_to_image(g->mlx, "textures/collect.xpm",
			&g->tex_collect.w, &g->tex_collect.h);
	if (!g->tex_wall.ptr || !g->tex_floor.ptr || !g->tex_player.ptr)
		print_error("texture load");
	if (!g->tex_exit.ptr || !g->tex_collect.ptr)
		print_error("texture load");
}

void	free_images(t_game *g)
{
	if (g->tex_wall.ptr)
		mlx_destroy_image(g->mlx, g->tex_wall.ptr);
	if (g->tex_floor.ptr)
		mlx_destroy_image(g->mlx, g->tex_floor.ptr);
	if (g->tex_player.ptr)
		mlx_destroy_image(g->mlx, g->tex_player.ptr);
	if (g->tex_exit.ptr)
		mlx_destroy_image(g->mlx, g->tex_exit.ptr);
	if (g->tex_collect.ptr)
		mlx_destroy_image(g->mlx, g->tex_collect.ptr);
}

static int	prepare_map(t_game *g, const char *path)
{
	if (!path)
		return (0);
	ft_memset(g, 0, sizeof(*g));
	is_ber_file(path);
	if (!load_map(path, &g->map))
		return (0);
	if (!is_rect_map(&g->map) || !check_map_charset(&g->map)
		|| !check_map_walls(&g->map) || !locate_player_collect(&g->map)
		|| !check_path(&g->map))
	{
		free_map(&g->map);
		return (0);
	}
	g->need = g->map.c_cnt;
	return (1);
}

int	init_game(t_game *g, const char *path)
{
	if (!prepare_map(g, path))
		return (0);
	g->mlx = mlx_init();
	if (!g->mlx)
	{
		free_map(&g->map);
		return (0);
	}
	g->win = mlx_new_window(g->mlx, g->map.w * TILE, g->map.h * TILE,
			"so_long");
	if (!g->win)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
		free_map(&g->map);
		return (0);
	}
	load_textures(g);
	return (1);
}
