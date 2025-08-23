/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:49:52 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/23 14:56:46 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	get_file_fd(t_pipex *pipex)
{
	pipex->infd = open(pipex->infile, O_RDONLY);
	if (pipex->infd < 0)
	{
		ft_putstr_fd("pipex:", 2);
		perror(pipex->infile);
	}
	pipex->outfd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfd < 0)
	{
		ft_putstr_fd("pipex:", 2);
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
		ft_putstr_fd("pipex: pipe: ", 2);
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
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		_exit(127);
	}
	execve(path, cmd, envp);
	if (errno == EACCES)
		_exit(126);
	free(path);
	_exit(126);
}

int	execute_pipex(t_pipex *pipex, char *envp[])
{
	int	status;

	status = 0;
	get_file_fd(pipex);
	make_pipe(pipex);
	pipex->pid1 = make_child_process_cmd1(pipex);
	if (pipex->pid1 == 0)
		execute_cmd(pipex->cmd1, envp);
	pipex->pid2 = make_child_process_cmd2(pipex);
	if (pipex->pid2 == 0)
		execute_cmd(pipex->cmd2, envp);
	if (pipex->infd >= 0)
		close(pipex->infd);
	close(pipex->outfd);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	if (pipex->pid1 > 0)
		waitpid(pipex->pid1, NULL, 0);
	if (pipex->pid2 > 0)
		waitpid(pipex->pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
