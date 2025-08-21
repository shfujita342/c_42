/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:02:34 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/21 22:27:04 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_cmd1(t_pipex *pipex)
{
	if (dup2(pipex->infile, STDIN_FILENO) == -1 || dup2(pipex->pipefd[1],
			STDOUT_FILENO))
		exit(1);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	close(pipex->infile);
}

void	redirect_cmd2(t_pipex *pipex)
{
	if (dup2(pipex->pipefd[0], STDIN_FILENO) || dup2(pipex->outfile,
			STDOUT_FILENO))
	{
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		close(pipex->infile);
	}
}

pid_t	make_child_process_cmd1(t_pipex *pipex)
{
	pid_t	pid;
	int		devnull;

	pid = fork;
	if (pid == -1)
	{
		write(2, "pipex: fork: ", 2);
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (pipex->infile < 0)
		{
			devnull = open("dev/null", O_RDONLY);
			if (devnull >= 0)
				pipex->infile = devnull;
		}
		redirect_cmd1(pipex);
	}
	return (pid);
}

pid_t	make_child_process_cmd2(t_pipex *pipex)
{
	pid_t	pid;

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
