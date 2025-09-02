/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:58:18 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/31 10:13:49 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_correct_charset(t_map *m)
{
	int	y;
	int	x;

	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			if (m->grid[y][x] != '0' && m->grid[y][x] != '1'
				&& m->grid[y][x] != 'C' && m->grid[y][x] != 'E'
				&& m->grid[y][x] != 'P')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	is_rect_map(t_map *m)
{
	int	y;

	y = 0;
	while (y < m->h)
	{
		if ((int)ft_strlen(m->grid[y]) != m->w)
			return (0);
		y++;
	}
	return (1);
}

int	is_surrounded_walls(t_map *m)
{
	int	x;
	int	y;

	x = 0;
	while (x < m->w)
	{
		if (m->grid[0][x] != '1' || m->grid[m->h - 1][x] != '1')
			return (0);
		x++;
	}
	y = 0;
	while (y < m->h)
	{
		if (m->grid[y][0] != '1' || m->grid[y][m->w - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

int	count_player_collect_exit(t_map *m)
{
	int	y;
	int	x;

	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			if (m->grid[y][x] == 'C')
				m->c_cnt++;
			else if (m->grid[y][x] == 'E')
				m->e_cnt++;
			else if (m->grid[y][x] == 'P')
			{
				m->p_cnt++;
				m->p_x = x;
				m->p_y = y;
			}
			x++;
		}
		y++;
	}
	return (!(m->c_cnt < 1 || m->e_cnt != 1 || m->p_cnt != 1));
}
