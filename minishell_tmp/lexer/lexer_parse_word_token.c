/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_word_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:44:58 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_quoted(const char *line, int *i) {
  char quote;
  int start;

  quote = line[*i];
  start = *i;
  (*i)++;
  while (line[*i] && line[*i] != quote)
    (*i)++;
  if (line[*i] == quote)
    (*i)++;
  return (*i - start);
}

static int	word_length(const char *line, int start) {
  int len;
  int i;

  len = 0;
  i = start;
  while (line[i] && line[i] != '|' && line[i] != '<' && line[i] != '>' &&
         !isspace(line[i])) {
    if ((line[i] == '\'' || line[i] == '"') && is_valid_quote(line, i))
      len += skip_quoted(line, &i);
    else {
      i++;
      len++;
    }
  }
  return (len);
}

static t_token	*create_word_token(const char *line, int *i) {
  int start;
  int len;
  t_token *tok;

  start = *i;
  len = word_length(line, start);
  tok = malloc(sizeof(t_token));
  if (!tok)
    return (NULL);
  tok->type = TOKEN_WORD;
  tok->value = ft_strndup(line + start, len);
  *i = start + len;
  return (tok);
}

t_token	*parse_word_token(const char *line, int *i) {
  return (create_word_token(line, i));
}
