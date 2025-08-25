/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fujit <fujit@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:49:52 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/25 06:24:58 by fujit            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	make_pipe(t_pipex *pipex)
{
	if (pipe(pipex->pipefd) < 0)
	{
		ft_putstr_fd("pipex: pipe: ", 2);
		perror("pipe");
		if (pipex->infd >= 0)
			close(pipex->infd);
		close(pipex->outfd);
		return (-1);
	}
	return (0);
}

void	execute_cmd(t_pipex *pipex, char **cmd, char *envp[])
{
	char	*path;

	path = resolve_path(cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found", 2);
		ft_putstr_fd("\n", 2);
		free_pipex(pipex);
		exit(127);
	}
	execve(path, cmd, envp);
	if (errno == EACCES)
	{
		// ft_putstr_fd("pipe: ",2);
		// perror(cmd[0]);
		print_errno2("pipex",cmd[0]);
		free_pipex(pipex);
		exit(126);
	}
	free(path);
	free_pipex(pipex);
	exit(126);
}

void	close_fds(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->infd >= 0)
	{
		close(pipex->infd);
		pipex->infd = -1;
	}
	if (pipex->outfd >= 0)
	{
		close(pipex->outfd);
		pipex->outfd = -1;
	}
	if (pipex->pipefd[0] >= 0)
	{
		close(pipex->pipefd[0]);
		pipex->pipefd[0] = -1;
	}
	if (pipex->pipefd[1] >= 0)
	{
		close(pipex->pipefd[1]);
		pipex->pipefd[1] = -1;
	}
}


int	execute_pipex(t_pipex *p, char *envp[])
{
	int	status;

	status = 0;
	if (make_pipe(p) < 0)
		return (1);
	p->pid1 = make_child_process_cmd1(p);
	if (p->pid1 == 0)
		execute_cmd(p, p->cmd1, envp);
	p->pid2 = make_child_process_cmd2(p);
	if (p->pid2 == 0)
		execute_cmd(p, p->cmd2, envp);
	if (p->pipefd[0] >= 0)
		close(p->pipefd[0]);
	if (p->pipefd[1] >= 0)
		close(p->pipefd[1]);
	p->pipefd[0] = -1;
	p->pipefd[1] = -1;
	if (p->pid1 > 0)
		waitpid(p->pid1, NULL, 0);
	if (p->pid2 > 0)
		waitpid(p->pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
