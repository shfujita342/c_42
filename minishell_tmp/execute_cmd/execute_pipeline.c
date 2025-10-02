/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:37:10 by shfujita          #+#    #+#             */
/*   Updated: 2025/10/02 15:51:57 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_child_process(pid_t *pids, int n, t_shell *sh)
{
	int	i;
	int	st;

	i = 0;
	while (i < n)
	{
		if (pids[i] > 0)
		{
			if (waitpid(pids[i], &st, 0) > 0)
			{
				if (WIFEXITED(st))
					sh->last_status = WEXITSTATUS(st);
				else if (WIFSIGNALED(st))
					sh->last_status = 128 + WTERMSIG(st);
			}
		}
		i++;
	}
}

static void	close_unused_pipe(int i, int n_pipes, int **pipes)
{
	if (i > 0 && pipes[i - 1][0] != -1)
	{
		close(pipes[i - 1][0]);
		pipes[i - 1][0] = -1;
	}
	if (i < n_pipes && pipes[i][1] != -1)
	{
		close(pipes[i][1]);
		pipes[i][1] = -1;
	}
}

static pid_t	*allocate_pids(int n_cmds, int **pipes, int n_pipes)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * n_cmds);
	if (!pids)
	{
		perror("malloc");
		close_pipes_fds(pipes, n_pipes);
		free_pipes(pipes, n_pipes);
		return (NULL);
	}
	return (pids);
}

static void	execute_pipeline_commands(t_shell *sh, pid_t *pids, int **pipes)
{
	int	i;
	int	n_cmds;
	int	n_pipes;

	i = 0;
	n_cmds = sh->current_pipeline->command_count;
	n_pipes = n_cmds - 1;
	while (i < n_cmds)
	{
		execute_cmd(sh, i, pipes, pids);
		if (n_pipes > 0)
			close_unused_pipe(i, n_pipes, pipes);
		i++;
	}
}

int	execute_pipeline(t_shell *sh)
{
	int		n_cmds;
	int		n_pipes;
	int		**pipes;
	pid_t	*pids;

	pipes = NULL;
	n_cmds = sh->current_pipeline->command_count;
	n_pipes = n_cmds - 1;
	pipes = make_pipes(n_pipes);
	if (n_pipes > 0 && !pipes)
		return (1);
	pids = allocate_pids(n_cmds, pipes, n_pipes);
	if (!pids)
		return (1);
	execute_pipeline_commands(sh, pids, pipes);
	wait_child_process(pids, n_cmds, sh);
	free(pids);
	free_pipes(pipes, n_pipes);
	free_pipeline(sh->current_pipeline);
	// free_pipes(pipes, n_pipes);
	return (sh->last_status);
}
