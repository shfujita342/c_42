/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:59:56 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens, int token_count)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (i < token_count)
	{
		if (tokens[i])
		{
			free(tokens[i]->value);
			free(tokens[i]);
		}
		i++;
	}
	free(tokens);
}

static t_pipeline	*set_pipeline(t_command **commands, int command_count)
{
	t_pipeline	*pipeline;
	int			i;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->commands = malloc(sizeof(t_command *) * (command_count + 1));
	if (!pipeline->commands)
	{
		free(pipeline);
		return (NULL);
	}
	pipeline->command_count = command_count;
	i = 0;
	while (i < command_count)
	{
		pipeline->commands[i] = commands[i];
		i++;
	}
	pipeline->commands[i] = NULL;
	return (pipeline);
}

t_command	**set_commands(const char *line, int *command_count, t_shell *shell)
{
	int			token_count;
	t_token		**tokens;
	t_command	**commands;

	token_count = 0;
	tokens = lexer(line, &token_count);
	if (!tokens)
		return (NULL);
	if (!check_syntax_errors(tokens, token_count))
	{
		free_tokens(tokens, token_count);
		return (NULL);
	}
	commands = change_tokens_to_commands(tokens, &token_count, command_count,
			shell);
	free_tokens(tokens, token_count);
	return (commands);
}

t_pipeline	*parse_line(const char *line, t_shell *shell)
{
	t_pipeline	*pipeline;
	t_command	**commands;
	int			command_count;

	command_count = 0;
	commands = set_commands(line, &command_count, shell);
	if (!commands)
		return (NULL);
	pipeline = set_pipeline(commands, command_count);
	return (pipeline);
}
