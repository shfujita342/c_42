/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:02:34 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/24 22:48:15 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	redirect_cmd1(t_pipex *p)
{
	int	fd;

	fd = open(p->infile, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("pipex:", 2);
		perror(p->infile);
		if (p->pipefd[0] >= 0)
			close(p->pipefd[0]);
		if (p->pipefd[1] >= 0)
			close(p->pipefd[1]);
		_exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1 || dup2(p->pipefd[1], STDOUT_FILENO) == -1)
	{
		close(fd);
		close_fds(p);
		_exit(1);
	}
	close(fd);
	close_fds(p);
}

void	redirect_cmd2(t_pipex *p)
{
	int	fd;

	if (dup2(p->pipefd[0], STDIN_FILENO) == -1)
	{
		close_fds(p);
		_exit(1);
	}
	if (p->pipefd[1] >= 0)
		close(p->pipefd[1]);
	fd = open(p->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("pipex:", 2);
		perror(p->outfile);
		close_fds(p);
		_exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		close_fds(p);
		_exit(1);
	}
	close(fd);
	close_fds(p);
}

pid_t	make_child_process_cmd1(t_pipex *p)
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
	{
		redirect_cmd1(p);
	}
	return (pid);
}

pid_t	make_child_process_cmd2(t_pipex *p)
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
	{
		redirect_cmd2(p);
	}
	return (pid);
}
