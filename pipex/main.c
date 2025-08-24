/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:48:16 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/24 18:41:01 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int		code;

	pipex = parse_args(argc, argv);
	code = execute_pipex(pipex, envp);
	close_fds(pipex);
	free_pipex(pipex);
	return (code);
}
