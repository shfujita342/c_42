/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command_fds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:13:44 by shfujita          #+#    #+#             */
/*   Updated: 2025/09/22 17:30:25 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_infd(int i, int **pipes, t_command *cmd, t_env *env_list)
{
	int		infd;
	int		count;
	char	*infile;

	count = 0;
	infd = -1;
	if (cmd->infile_count > 0) //ここをcmd->infile[count]にしたら死んだ
	{
		while (count < cmd->infile_count)
		{
			if (!cmd->is_heredoc[count])
			{
				infile = cmd->infile[count];
				infd = open(infile, O_RDONLY);
				if (infd < 0)
					return (-1);
			}
			else
			{
				(void)env_list;
				// infd = execute_heredoc(cmd->infile[count],
				// 		cmd->in_quotes[count], env_list);
			}
			count++;
		}
	}
	else if (i > 0)
		infd = pipes[i - 1][0];
	if (infd >= 0)
	{
		if (dup2(infd, STDIN_FILENO) < 0)
		{
			close(infd);
			return (-1);
		}
		close(infd);
	}
	return (0);
}

static int	set_outfd(int i, int n_pipes, int **pipes, t_command *cmd)
{
	int		outfd;
	int		num_fd;
	int		flags;
	char	*outfile;
	int		count;

	outfd = -1;
	num_fd = cmd->num_outfd;
	count = 0;
	if (cmd->outfile_count > 0) //ここをcmd->outfile[count]にしたら死んだ
	{
		while (count < cmd->outfile_count)
		{
			outfile = cmd->outfile[count];
			if (cmd->is_append[count])
				flags = O_WRONLY | O_CREAT | O_APPEND;
			else
				flags = O_WRONLY | O_CREAT | O_TRUNC;
			outfd = open(outfile, flags, 0644);
			if (outfd < 0)
				return (-1);
			count++;
		}
	}
	else if (i < n_pipes)
		outfd = pipes[i][1];
	else if (num_fd != 1)
	{
		is_valid_fd(num_fd);
	}
	if (outfd >= 0)
	{
		if (dup2(outfd, STDOUT_FILENO) < 0)
		{
			close(outfd);
			return (-1);
		}
		close(outfd);
	}
	return (0);
}

void	set_command_fds(t_shell *sh, int i, int **pipes)
{
	t_command	*cmd;
	int			n_pipes;

	cmd = sh->current_pipeline->commands[i];
	n_pipes = sh->current_pipeline->command_count - 1;
	if (set_infd(i, pipes, cmd, sh->env_list) < 0 || set_outfd(i, n_pipes,
			pipes, cmd) < 0)
	{
		free_and_close_all(sh->current_pipeline, pipes, n_pipes);
		exit(1);
	}
	close_pipes_fds(pipes, n_pipes);
}
