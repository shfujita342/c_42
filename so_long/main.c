/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:55:44 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/31 12:16:06 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static int	arg_error(void)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Usage: ./so_long maps/file.ber", 2);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (arg_error());
	if (init_game(&g, argv[1]) == 0)
		print_error("init failed");
	render(&g);
	mlx_hook(g.win, 2, 1L, on_key, &g);
	mlx_hook(g.win, 17, 0, on_close, &g);
	mlx_loop(g.mlx);
	return (0);
}
