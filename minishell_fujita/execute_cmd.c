/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:44:08 by shfujita          #+#    #+#             */
/*   Updated: 2025/09/19 14:21:28 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	set_infd(int i, int **pipes, t_command *cmd, t_env *env_list)
// {
// 	int		infd;
// 	int		count;
// 	char	*infile;

// 	count = 0;
// 	infd = -1;
// 	if (cmd->infile[count])
// 	{
// 		while (count < cmd->infile_count)
// 		{
// 			if (!cmd->is_heredoc[count])
// 			{
// 				infile = cmd->infile[count];
// 				infd = open(cmd->infile, O_RDONLY);
// 				if (infd < 0)
// 					return (-1);
// 			}
// 			else
// 			{
// 				infd = execute_heredoc(cmd->infile[count],
// 						cmd->in_quotes[count], env_list);
// 			}
// 			count++;
// 		}#include <aio.h>
// 	}
// 	else if (i > 0)
// 		infd = pipes[i - 1][0];
// 	if (infd >= 0)
// 	{
// 		if (dup2(infd, STDIN_FILENO) < 0)
// 		{
// 			close(infd);
// 			return (-1);
// 		}
// 		close(infd);
// 	}
// 	return (0);
// }

// int	set_outfd(int i, int n_pipes, int (*pipes)[2], t_command *cmd)
// {
// 	int		outfd;
// 	int		flags;
// 	char	*outfile;
// 	int		count;

// 	outfd = -1;
// 	count = 0;
// 	if (cmd->outfile[count])
// 	{
// 		while (count < cmd->outfile_count)
// 		{
// 			outfile = cmd->outfile[count];
// 			if (cmd->is_append[count])
// 				flags = O_WRONLY | O_CREAT | O_APPEND;
// 			else
// 				flags = O_WRONLY | O_CREAT | O_TRUNC;
// 			outfd = open(outfile, flags, 0644);
// 			if (outfd < 0)
// 				return (-1);
// 			count++;
// 		}
// 	}
// 	else if (i < n_pipes)
// 		outfd = pipes[i][1];
// 	if (outfd >= 0)
// 	{
// 		if (dup2(outfd, STDOUT_FILENO) < 0)
// 		{
// 			close(outfd);
// 			return (-1);
// 		}
// 		close(outfd);
// 	}
// 	return (0);
// }

void	free_and_close_all(t_pipeline *pipeline, int **pipes, int n_pipes)
{
	close_pipes_fds(pipes, n_pipes);
	free_pipes(pipes, n_pipes);
	free_pipeline(pipeline);
}

void	execute_cmd(t_shell *sh, int i, int **pipes, pid_t *pids)
{
	t_command	*cmd;
	char		**envp;
	int			n_pipes;
	char		*path;

	cmd = sh->current_pipeline->commands[i];
	n_pipes = sh->current_pipeline->command_count - 1;
	pids[i] = fork();
	if (pids[i] < 0)
		return ;
	if (pids[i] == 0)
	{
		set_command_fds(sh, i, pipes);
		path = resolve_path(cmd->cmd[0], sh->env_list);
		if (!path)
		{
			perror(cmd->cmd[0]);
			free_and_close_all(sh->current_pipeline, pipes, n_pipes);
			exit(127);
		}
		envp = convert_env_to_environ(sh->env_list);
		execve(path, cmd->cmd, envp);
		perror(cmd->cmd[0]);
		exit(126);
	}
}
