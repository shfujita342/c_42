/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_tokens_to_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:09:37 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	**get_next_pipe(t_token **tokens, int *idx, int tok_count)
{
	t_token	**pipe_tokens;
	int		capacity;
	int		n;

	capacity = 16;
	n = 0;
	pipe_tokens = malloc(sizeof(t_token *) * capacity);
	if (!pipe_tokens)
		return (NULL);
	while (*idx < tok_count && tokens[*idx]->type != TOKEN_PIPE)
	{
		if (n + 1 >= capacity)
		{
			capacity *= 2;
			pipe_tokens = realloc(pipe_tokens, sizeof(t_token *) * capacity);
		}
		pipe_tokens[n] = tokens[*idx];
		n++;
		(*idx)++;
	}
	pipe_tokens[n] = NULL;
	if (*idx < tok_count && tokens[*idx]->type == TOKEN_PIPE)
		(*idx)++;
	return (pipe_tokens);
}

static void	*safe_expand_commands(t_command **commands, int *capacity,
		int cmd_count)
{
	t_command	**tmp;

	*capacity *= 2;
	tmp = realloc(commands, sizeof(t_command *) * (*capacity));
	if (!tmp)
	{
		free_commands(commands, cmd_count);
		return (NULL);
	}
	return (tmp);
}

static t_command	*set_command_from_pipe_tokens(t_token **pipe_tokens,
		t_shell *shell)
{
	t_command	*command;
	int			i;

	command = init_command();
	if (!command)
		return (NULL);
	i = 0;
	while (pipe_tokens[i])
	{
		if (pipe_tokens[i]->type == TOKEN_WORD)
			set_cmd(command, pipe_tokens[i]->value, &i, shell);
		else if (pipe_tokens[i]->type == TOKEN_REDIR_IN && pipe_tokens[i + 1])
			set_infile(command, pipe_tokens[i + 1]->value, &i);
		else if (pipe_tokens[i]->type == TOKEN_REDIR_OUT && pipe_tokens[i + 1])
			set_outfile(command, pipe_tokens[i + 1]->value, &i);
		else if (pipe_tokens[i]->type == TOKEN_HEREDOC && pipe_tokens[i + 1])
			set_heredoc(command, pipe_tokens[i + 1]->value, &i);
		else if (pipe_tokens[i]->type == TOKEN_APPEND && pipe_tokens[i + 1])
			set_append(command, pipe_tokens[i + 1]->value, &i);
	}
	return (command);
}

t_command	**change_tokens_to_commands(t_token **tokens, int *tok_count,
		int *cmd_count, t_shell *shell)
{
	int			i;
	t_token		**pipe_tokens;
	t_command	**commands;
	int			capacity;

	i = 0;
	capacity = 16;
	commands = malloc(sizeof(t_command *) * capacity);
	while (i < *tok_count)
	{
		pipe_tokens = get_next_pipe(tokens, &i, *tok_count);
		if (!pipe_tokens)
			return (free_commands(commands, *cmd_count), NULL);
		if (*cmd_count >= capacity)
			commands = safe_expand_commands(commands, &capacity, *cmd_count);
		if (!commands)
			return (NULL);
		commands[*cmd_count] = set_command_from_pipe_tokens(pipe_tokens, shell);
		free(pipe_tokens);
		if (!commands[*cmd_count])
			return (free_commands(commands, *cmd_count), NULL);
		(*cmd_count)++;
	}
	return (commands);
}
