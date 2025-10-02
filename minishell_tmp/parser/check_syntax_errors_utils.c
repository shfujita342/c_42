/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:51:39 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(const char *msg)
{
	ft_fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n",
		msg);
}

bool	is_redirect(t_token tok)
{
	return (tok.type == TOKEN_REDIR_IN || tok.type == TOKEN_REDIR_OUT
		|| tok.type == TOKEN_APPEND || tok.type == TOKEN_HEREDOC);
}

bool	is_pipe(t_token tok)
{
	return (tok.type == TOKEN_PIPE);
}
