/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:31:01 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 13:47:36 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(const char *line, int i)
{
	while (line[i] && isspace(line[i]))
		i++;
	return (i);
}

static t_token	*parse_pipe_token(int *idx)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = TOKEN_PIPE;
	tok->value = ft_strdup("|");
	(*idx)++;
	return (tok);
}

static t_token	*next_token(const char *line, int *idx)
{
	int		i;
	t_token	*tok;

	i = *idx;
	i = skip_spaces(line, i);
	if (!line[i])
		return (NULL);
	if (line[i] == '|')
		tok = parse_pipe_token(&i);
	else if (line[i] == '<' || line[i] == '>')
		tok = parse_redirect_token(line, &i);
	else
		tok = parse_word_token(line, &i);
	*idx = i;
	return (tok);
}

t_token	**lexer(const char *line, int *count)
{
	int		capacity;
	int		idx;
	t_token	**tokens;
	int		n;
	t_token	*tok;

	capacity = 16;
	idx = 0;
	tokens = malloc(sizeof(t_token *) * capacity);
	if (!tokens)
		return (NULL);
	n = 0;
	tok = next_token(line, &idx);
	while (tok)
	{
		if (n >= capacity)
		{
			capacity *= 2;
			tokens = realloc(tokens, sizeof(t_token *) * capacity);
		}
		tokens[n++] = tok;
		tok = next_token(line, &idx);
	}
	*count = n;
	return (tokens);
}
