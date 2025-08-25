/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:02:34 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/25 17:07:04 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	redirect_cmd1(t_pipex *p)
{
	p->infd = open(p->infile, O_RDONLY);
	if (p->infd < 0)
	{
		print_errno2("pipex", p->infile);
		close_fds(p);
		free_pipex(p);
		exit(1);
	}
	if (dup2(p->infd, STDIN_FILENO) == -1 || dup2(p->pipefd[1],
			STDOUT_FILENO) == -1)
	{
		close_fds(p);
		free_pipex(p);
		exit(1);
	}
	close_fds(p);
}

void	redirect_cmd2(t_pipex *p)
{
	if (dup2(p->pipefd[0], STDIN_FILENO) == -1)
	{
		close_fds(p);
		free_pipex(p);
		exit(1);
	}
	p->outfd = open(p->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->outfd < 0)
	{
		print_errno2("pipex", p->outfile);
		close_fds(p);
		free_pipex(p);
		exit(1);
	}
	if (dup2(p->outfd, STDOUT_FILENO) == -1)
	{
		close_fds(p);
		free_pipex(p);
		exit(1);
	}
	close_fds(p);
}

pid_t	make_child_process(t_pipex *p, int flag)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		print_errno2("pipex: fork: ", "fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (flag)
			redirect_cmd1(p);
		else
			redirect_cmd2(p);
	}
	return (pid);
}
