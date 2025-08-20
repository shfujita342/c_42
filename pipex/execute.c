/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:49:52 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/20 23:03:06 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_file_fd(t_pipex *pipex)
{
	pipex->infd = open(pipex->infile, O_RDONLY);
	if (pipex->infd < 0)
	{
		perror("open infile");
		exit(1);
	}
	pipex->outfd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfd < 0)
	{
		write(2, "pipex: ", 7);
		perror(pipex->outfile);
		if (pipex->infd >= 0)
			close(pipex->infd);
		exit(1);
	}
}

void	make_pipe(int fd[2], t_pipex *pipex)
{
	if (pipe(fd) < 0)
	{
		write(2, "pipex: pipe: ", 13);
		perror("pipe");
		if (pipex->infd >= 0)
			close(pipex->infd);
		close(pipex->outfd);
		exit(1);
	}
}

void	execute_pipex(t_pipex *pipex, char *envp[])
{
	int	fd[2];

	get_file_fd(pipex);
	make_pipe(fd, pipex);
	make_child_process(pipex, envp);
}
