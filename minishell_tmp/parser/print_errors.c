/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:00:15 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_system_error(const char *msg)
{
	if (msg)
		ft_fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	else
		ft_fprintf(stderr, "%s\n", strerror(errno));
	return (-1);
}

void	print_command_error(const char *msg, const char *cmd)
{
	if (!msg && !cmd)
		return ;
	if (msg && cmd)
		ft_fprintf(stderr, "minishell: %s: %s\n", msg, cmd);
	else if (msg)
		ft_fprintf(stderr, "minishell: %s\n", msg);
	else if (cmd)
		ft_fprintf(stderr, "minishell: %s\n", cmd);
}
