/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:02:33 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/29 16:25:20 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_error(const char *msg)
{
	putstr_fd("Error\n", 2);
	if (msg)
	{
		putstr_fd(msg, 2);
		putstr_fd("\n", 2);
	}
	exit(1);
}
