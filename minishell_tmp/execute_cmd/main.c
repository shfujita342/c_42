/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:57:04 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	(void)argc;
	(void)argv;
	set_signal(SIGCTX_PARENT);
	shell.env_list = copy_env(envp);
	shell.last_status = 0;
	shell.current_pipeline = NULL;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (line && *line)
			add_history(line);
		shell.current_pipeline = parse_line(line, &shell);
		if (shell.current_pipeline)
			execute_pipeline(&shell);
		free(line);
		// free_pipeline(shell.current_pipeline);
		shell.current_pipeline = NULL;
	}
	rl_clear_history();
	free_env_list(shell.env_list);
	return (shell.last_status);
}
