/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:49:52 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/25 19:57:23 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	make_pipe(t_pipex *pipex)
{
	if (pipe(pipex->pipefd) < 0)
	{
		print_errno2("pipex: pipe: ", "pipe");
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
		print_errno2("pipex", cmd[0]);
		free(path);
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

void	print_errno2(const char *pfx, const char *name)
{
	char	*msg1;
	char	*msg2;
	char	*msg3;
	char	*full;

	msg1 = ft_strjoin(pfx, ": ");
	msg2 = ft_strjoin(msg1, name);
	free(msg1);
	msg3 = ft_strjoin(msg2, ": ");
	free(msg2);
	full = ft_strjoin(msg3, strerror(errno));
	free(msg3);
	msg1 = ft_strjoin(full, "\n");
	free(full);
	if (!msg1)
		return ;
	write(2, msg1, strlen(msg1));
	free(msg1);
}

int	execute_pipex(t_pipex *p, char *envp[])
{
	int	status;

	status = 0;
	if (make_pipe(p) < 0)
		return (1);
	p->pid1 = make_child_process(p, 1);
	if (p->pid1 == 0)
		execute_cmd(p, p->cmd1, envp);
	p->pid2 = make_child_process(p, 0);
	if (p->pid2 == 0)
		execute_cmd(p, p->cmd2, envp);
	close_fds(p);
	if (p->pid1 > 0)
		waitpid(p->pid1, NULL, 0);
	if (p->pid2 > 0)
		waitpid(p->pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
