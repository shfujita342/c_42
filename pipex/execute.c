/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:49:52 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/21 23:21:35 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_file_fd(t_pipex *pipex)
{
	pipex->infd = open(pipex->infile, O_RDONLY);
	if (pipex->infd < 0)
	{
		write(2, "pipex:", 6);
		perror(pipex->infile);
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

void	make_pipe(t_pipex *pipex)
{
	if (pipe(pipex->pipefd) < 0)
	{
		write(2, "pipex: pipe: ", 13);
		perror("pipe");
		if (pipex->infd >= 0)
			close(pipex->infd);
		close(pipex->outfd);
		exit(1);
	}
}

void	execute_cmd(char **cmd, char *envp[])
{
	char	*path;

	path = resolve_path(cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd("pipex: empty command\n", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	execve(path, cmd, envp);
	if (errno == EACCES)
		exit(126);
	free(path);
	exit(126);
}

void	execute_pipex(t_pipex *pipex, char *envp[])
{
	int	status;

	status = 0;
	get_file_fd(pipex);
	make_pipe(pipex);
	pipex->pid1 = make_child_process_cmd1(pipex);
	if (pipex->pid1 == 0)
		execute_cmd(pipex->cmd1, envp);
	pipex->pid2 = make_child_prosess_cmd2(pipex);
	if (pipex->pid2 == 0)
		execute_cmd(pipex->cmd2, envp);
	if (pipex->infile >= 0)
		close(pipex->infile);
	close(pipex->outfile);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	if (pipex->pid1 > 0)
		waitpid(pipex->pid1, NULL, 0);
	if (pipex->pid2 > 0)
		waitpid(pipex->pid2, &status, 0);
}
