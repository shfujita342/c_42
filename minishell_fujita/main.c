/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:57:04 by yseto             #+#    #+#             */
/*   Updated: 2025/09/27 19:32:00 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

static void	sigint_handler(int signo)
{
	g_last_signal = signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	set_parent_signal_handlers(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigation(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigation(SIGQUIT, &sa, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	shell.env_list = copy_env(envp);
	shell.last_status = 0;
	shell.current_pipeline = NULL;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (line && *line)
			add_history(line);
		if (g_last_signal == SIGINT)
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
