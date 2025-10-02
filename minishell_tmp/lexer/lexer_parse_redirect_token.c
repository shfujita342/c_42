/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_redirect_token.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:46:16 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_less_redirect(const char *line, int *i) {
  if (line[*i + 1] == '<') {
    *i += 2;
    return (TOKEN_HEREDOC);
  } else {
    (*i)++;
    return (TOKEN_REDIR_IN);
  }
}

static t_token_type	get_greater_redirect(const char *line, int *i) {
  if (line[*i + 1] == '>') {
    *i += 2;
    return (TOKEN_APPEND);
  } else {
    (*i)++;
    return (TOKEN_REDIR_OUT);
  }
}

static t_token_type	get_redirect_type(const char *line, int *i) {
  if (line[*i] == '<')
    return (get_less_redirect(line, i));
  else
    return (get_greater_redirect(line, i));
}

static t_token	*create_redirect_token(t_token_type type, const char *value) {
  t_token *tok;

  tok = malloc(sizeof(t_token));
  if (!tok)
    return (NULL);
  tok->type = type;
  tok->value = ft_strdup(value);
  return (tok);
}

t_token	*parse_redirect_token(const char *line, int *idx) {
  int i;
  t_token_type type;
  char *value;

  i = *idx;
  type = get_redirect_type(line, &i);
  if (type == TOKEN_REDIR_IN)
    value = "<";
  else if (type == TOKEN_REDIR_OUT)
    value = ">";
  else if (type == TOKEN_HEREDOC)
    value = "<<";
  else if (type == TOKEN_APPEND)
    value = ">>";
  else
    return (NULL);
  *idx = i;
  return (create_redirect_token(type, value));
}
