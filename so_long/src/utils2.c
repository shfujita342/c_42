/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:02:05 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/31 11:30:35 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	ft_memset(m, 0, sizeof(*m));
}

int	is_blank_line(const char *s)
{
	if (!s || !s[0])
		return (1);
	if (s[0] == '\n' && s[1] == '\0')
		return (1);
	return (0);
}
