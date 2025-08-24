/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:48:16 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/24 19:53:59 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_pipex(t_pipex *p)
{
	p->infd = -1;
	p->outfd = -1;
	p->pipefd[0] = -1;
	p->pipefd[1] = -1;
	p->pid1 = -1;
	p->pid2 = -1;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int		code;

	pipex = parse_args(argc, argv);
	init_pipex(pipex);
	code = execute_pipex(pipex, envp);
	close_fds(pipex);
	free_pipex(pipex);
	return (code);
}
