/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:24:26 by shfujita          #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

static void	sigint_handler_parent(int signo)
{
	(void)signo;
	g_last_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_struct_sigaction(int flag, struct sigaction *sa_sigint,
		struct sigaction *sa_sigquit)
{
	sigemptyset(&(sa_sigint->sa_mask));
	sigemptyset(&(sa_sigquit->sa_mask));
	sa_sigint->sa_flags = 0;
	sa_sigquit->sa_flags = 0;
	if (flag == SIGCTX_PARENT)
	{
		sa_sigint->sa_handler = sigint_handler_parent;
		sa_sigquit->sa_handler = SIG_IGN;
		sa_sigint->sa_flags = SA_RESTART;
		sigaddset(&(sa_sigint->sa_mask), SIGQUIT);
	}
	else if (flag == SIGCTX_CHILD)
	{
		sa_sigint->sa_handler = SIG_DFL;
		sa_sigquit->sa_handler = SIG_DFL;
	}
	else if (flag == SIGCTX_HEREDOC)
	{
		sa_sigint->sa_handler = SIG_DFL;
		sa_sigquit->sa_handler = SIG_IGN;
	}
}

void	set_signal(int flag)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	rl_catch_signals = 0;
	set_struct_sigaction(flag, &sa_sigint, &sa_sigquit);
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}
