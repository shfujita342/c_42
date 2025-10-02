/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:58:55 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_quote(const char *str, int i)
{
	char	quote;
	int		j;

	quote = str[i];
	j = i + 1;
	while (str[j])
	{
		if (str[j] == quote)
			return (1);
		j++;
	}
	return (0);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_command));
	cmd->cmd = malloc(sizeof(char *));
	if (!cmd->cmd)
	{
		free(cmd);
		return (NULL);
	}
	cmd->cmd[0] = NULL;
	cmd->infile_count = 0;
	cmd->infile = NULL;
	cmd->is_heredoc = NULL;
	cmd->in_quotes = NULL;
	cmd->outfile_count = 0;
	cmd->outfile = NULL;
	cmd->is_append = NULL;
	return (cmd);
}
