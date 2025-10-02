/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:08:22 by shfujita          #+#    #+#             */
/*   Updated: 2025/10/02 20:24:31 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(const char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static void	execute_builtin(char **argv, t_shell *shell)
{
	if (!argv || !argv[0])
		return ;
	if (strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv));
	else if (strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv));
	else if (strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(argv));
	else if (strcmp(argv[0], "export") == 0)
		return (ft_export(argv));
	else if (strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv));
	else if (strcmp(argv[0], "env") == 0)
		return (ft_env(argv, shell->env_list));
	else if (strcmp(argv[0], "exit") == 0)
		return (ft_exit(argv));
}

static void	execute_external(int i, int **pipes, pid_t *pids, t_shell *sh)
{
	t_command	*cmd;
	int			n_pipes;
	char		*path;

	cmd = sh->current_pipeline->commands[i];
	n_pipes = sh->current_pipeline->command_count;
	pids[i] = fork();
	if (pids[i] < 0)
		return ;
	if (pids[i] == 0)
	{
		set_signal(SIGCTX_CHILD);
		close_pipes_fds(pipes, n_pipes);
		path = resolve_path(cmd->cmd[0], sh->env_list);
		if (!path)
		{
			perror(cmd->cmd[0]);
			free_and_close_all(sh->current_pipeline, pipes, n_pipes);
			exit(127);
		}
		execve(path, cmd->cmd, convert_env_to_environ(sh->env_list));
		perror(cmd->cmd[0]);
		exit(126);
	}
}

void	execute_cmd(t_shell *sh, int i, int **pipes, pid_t *pids)
{
	t_command	*cmd;

	cmd = sh->current_pipeline->commands[i];
	set_command_fds(sh, i, pipes);
	if (is_builtin(cmd->cmd[0]))
		return (execute_builtin(cmd->cmd, sh));
	else
		return (execute_external(cmd, i, pids, sh));
	execute_external(i, pipes, pids, sh);
}

// void	execute_cmd(t_shell *sh, int i, int **pipes, pid_t *pids)
// {
// 	t_command	*cmd;
// 	char		**envp;
// 	int			n_pipes;
// 	char		*path;

// 	n_pipes = sh->current_pipeline->command_count - 1;
// 	cmd = sh->current_pipeline->commands[i];
// 	set_command_fds(sh, i, pipes);
// 	pids[i] = fork();
// 	if (pids[i] < 0)
// 		return ;
// 	if (pids[i] == 0)
// 	{
// 		set_signal(SIGCTX_CHILD);
// 		close_pipes_fds(pipes, n_pipes);
// 		path = resolve_path(cmd->cmd[0], sh->env_list);
// 		if (!path)
// 		{
// 			perror(cmd->cmd[0]);
// 			free_and_close_all(sh->current_pipeline, pipes, n_pipes);
// 			exit(127);
// 		}
// 		envp = convert_env_to_environ(sh->env_list);
// 		execve(path, cmd->cmd, envp);
// 		perror(cmd->cmd[0]);
// 		exit(126);
// 	}
// }
