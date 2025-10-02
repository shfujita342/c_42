/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:24:27 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_start_pipe(t_token **tokens, int count)
{
	if (count > 0 && is_pipe(*tokens[0]))
	{
		print_syntax_error("|");
		return (false);
	}
	return (true);
}

static bool	check_end_token(t_token **tokens, int count)
{
	if (count == 0)
		return (true);
	if (is_pipe(*tokens[count - 1]))
	{
		print_syntax_error("|");
		return (false);
	}
	if (is_redirect(*tokens[count - 1]))
	{
		print_syntax_error("newline");
		return (false);
	}
	return (true);
}

static bool	check_consecutive_pipes(t_token **tokens, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (is_pipe(*tokens[i]) && is_pipe(*tokens[i + 1]))
		{
			print_syntax_error("|");
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_redirect_followed_by_word(t_token **tokens, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (is_redirect(*tokens[i]) && (tokens[i + 1]->type != TOKEN_WORD))
		{
			print_syntax_error(tokens[i + 1]->value);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_syntax_errors(t_token **tokens, int count)
{
	if (!check_start_pipe(tokens, count))
		return (false);
	if (!check_consecutive_pipes(tokens, count))
		return (false);
	if (!check_redirect_followed_by_word(tokens, count))
		return (false);
	if (!check_end_token(tokens, count))
		return (false);
	return (true);
}
