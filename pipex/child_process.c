/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:02:34 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/23 14:09:35 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_cmd1(t_pipex *pipex)
{
	if (dup2(pipex->infd, STDIN_FILENO) == -1 || dup2(pipex->pipefd[1],
			STDOUT_FILENO) == -1)
		_exit(1);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	close(pipex->infd);
}

void	redirect_cmd2(t_pipex *pipex)
{
	if (dup2(pipex->pipefd[0], STDIN_FILENO) == -1 || dup2(pipex->outfd,
			STDOUT_FILENO) == -1)
		_exit(1);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	close(pipex->outfd);
}

pid_t	make_child_process_cmd1(t_pipex *pipex)
{
	pid_t	pid;
	int		devnull;

	pid = fork();
	if (pid == -1)
	{
		write(2, "pipex: fork: ", 13);
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (pipex->infd < 0)
		{
			devnull = open("/dev/null", O_RDONLY);
			if (devnull >= 0)
				pipex->infd = devnull;
		}
		redirect_cmd1(pipex);
	}
	return (pid);
}

pid_t	make_child_process_cmd2(t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		write(2, "pipex: fork: ", 13);
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		redirect_cmd2(pipex);
	return (pid);
}
