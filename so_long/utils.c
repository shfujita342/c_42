/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:01:19 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/31 12:04:43 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**dup_grid(char **grid, int h)
{
	int		i;
	char	**dup;

	dup = malloc(sizeof(char *) * (h + 1));
	if (!dup)
		print_error("malloc");
	i = 0;
	while (i < h)
	{
		dup[i] = ft_strdup(grid[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	gnl_drain(int fd)
{
	char	*s;

	s = get_next_line(fd);
	while (s)
	{
		free(s);
		s = get_next_line(fd);
	}
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
	ft_memset(m, 0, sizeof(*m));
}

void	print_error(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
	{
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(1);
}
