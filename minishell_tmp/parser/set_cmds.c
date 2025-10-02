/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:19:48 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_infile(t_command *command, const char *token_value, int *idx)
{
	int		count;
	char	*stripped;

	count = command->infile_count;
	stripped = remove_quotes(token_value);
	command->infile = realloc(command->infile, sizeof(char *) * (count + 2));
	command->is_heredoc = realloc(command->is_heredoc, sizeof(int) * (count
				+ 1));
	command->in_quotes = realloc(command->in_quotes, sizeof(int) * (count + 1));
	if (!command->infile || !command->is_heredoc || !command->in_quotes)
	{
		perror("realloc failed");
		exit(EXIT_FAILURE);
	}
	command->infile[count] = stripped;
	command->infile[count + 1] = NULL;
	command->is_heredoc[count] = 0;
	command->in_quotes[count] = 0;
	command->infile_count++;
	(*idx) += 2;
}

void	set_outfile(t_command *command, const char *token_value, int *idx)
{
	int		count;
	char	*stripped;

	count = command->outfile_count;
	stripped = remove_quotes(token_value);
	command->outfile = realloc(command->outfile, sizeof(char *) * (count + 2));
	command->is_append = realloc(command->is_append, sizeof(int) * (count + 1));
	if (!command->outfile || !command->is_append)
	{
		perror("realloc failed");
		exit(EXIT_FAILURE);
	}
	command->outfile[count] = stripped;
	command->outfile[count + 1] = NULL;
	command->is_append[count] = 0;
	command->outfile_count++;
	(*idx) += 2;
}

void	set_append(t_command *command, const char *token_value, int *idx)
{
	int		count;
	char	*stripped;

	count = command->outfile_count;
	stripped = remove_quotes(token_value);
	command->outfile = realloc(command->outfile, sizeof(char *) * (count + 2));
	command->is_append = realloc(command->is_append, sizeof(int) * (count + 1));
	if (!command->outfile || !command->is_append)
	{
		perror("realloc failed");
		exit(EXIT_FAILURE);
	}
	command->outfile[count] = stripped;
	command->outfile[count + 1] = NULL;
	command->is_append[count] = 1;
	command->outfile_count++;
	(*idx) += 2;
}

void	set_heredoc(t_command *command, const char *token_value, int *idx)
{
	int		count;
	int		quoted;
	char	*stripped;

	count = command->infile_count;
	quoted = 0;
	stripped = remove_quotes_with_flag(token_value, &quoted);
	command->infile = realloc(command->infile, sizeof(char *) * (count + 2));
	command->is_heredoc = realloc(command->is_heredoc, sizeof(int) * (count
				+ 1));
	command->in_quotes = realloc(command->in_quotes, sizeof(int) * (count + 1));
	if (!command->infile || !command->is_heredoc || !command->in_quotes)
	{
		perror("realloc failed");
		exit(EXIT_FAILURE);
	}
	command->infile[count] = stripped;
	command->infile[count + 1] = NULL;
	command->is_heredoc[count] = 1;
	command->in_quotes[count] = quoted;
	command->infile_count++;
	(*idx) += 2;
}

void	set_cmd(t_command *command, const char *token_value, int *idx,
		t_shell *shell)
{
	int		cmd_count;
	char	*expanded;

	cmd_count = count_cmd(command->cmd);
	command->cmd = realloc(command->cmd, sizeof(char *) * (cmd_count + 2));
	if (!command->cmd)
	{
		perror("realloc failed");
		exit(EXIT_FAILURE);
	}
	expanded = expand_env(token_value, shell);
	command->cmd[cmd_count] = expanded;
	command->cmd[cmd_count + 1] = NULL;
	(*idx)++;
}
