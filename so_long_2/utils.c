/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:01:19 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/30 18:41:06 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*safe_malloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		print_error("malloc");
	return (p);
}

char	**dup_grid(char **grid, int h)
{
	int		i;
	char	**dup;

	dup = (char **)safe_malloc(sizeof(char *) * (h + 1));
	i = 0;
	while (i < h)
	{
		dup[i] = ft_strdup(grid[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

// gnl の内部スタッシュを解放させるため、EOFまで読み切る
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
