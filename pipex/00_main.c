/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:48:16 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/25 17:17:29 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_pipex(t_pipex *p)
{
	if (!p)
		return ;
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
	int		res;

	pipex = parse_args(argc, argv);
	if (!pipex)
		return (1);
	init_pipex(pipex);
	res = execute_pipex(pipex, envp);
	// close_fds(pipex);
	free_pipex(pipex);
	return (res);
}
