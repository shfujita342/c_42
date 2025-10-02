/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:37:39 by shfujita          #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(int **pipes, int size)
{
	int	i;

	if (!pipes || !*pipes || size <= 0)
		return ;
	i = 0;
	while (i < size)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	close_pipes_fds(int **pipes, int size)
{
	int	i;

	if (!pipes || !*pipes || size <= 0)
		return ;
	i = 0;
	while (i < size)
	{
		if (pipes[i][0] != -1)
			close(pipes[i][0]);
		if (pipes[i][1] != -1)
			close(pipes[i][1]);
		i++;
	}
}

static int	**allocate_pipes(int n_pipes)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = malloc(sizeof(int *) * (n_pipes));
	if (!pipes)
		return (NULL);
	while (i < n_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			free_pipes(pipes, i);
			return (NULL);
		}
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		i++;
	}
	return (pipes);
}

int	**make_pipes(int n_pipes)
{
	int	i;
	int	**pipes;

	if (n_pipes < 1)
		return (NULL);
	i = 0;
	pipes = allocate_pipes(n_pipes);
	if (!pipes)
	{
		perror("malloc");
		return (NULL);
	}
	while (i < n_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
