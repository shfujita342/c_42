/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:24:49 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_str_array(char **arr, int count)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_null_terminated_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	free_null_terminated_array(cmd->cmd);
	free_str_array(cmd->infile, cmd->infile_count);
	free_str_array(cmd->outfile, cmd->outfile_count);
	free(cmd->is_append);
	free(cmd->is_heredoc);
	free(cmd->in_quotes);
	free(cmd);
}

void	free_commands(t_command **commands, int command_count)
{
	int	i;

	if (!commands)
		return ;
	i = 0;
	while (i < command_count)
	{
		free_command(commands[i]);
		i++;
	}
	free(commands);
}

void	free_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	free_commands(pipeline->commands, pipeline->command_count);
	free(pipeline);
}
