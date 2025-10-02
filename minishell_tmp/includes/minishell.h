/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:57:00 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 20:33:42 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# include "libft.h"
# include <aio.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define MAX_ARGS 256
# define MAX_COMMANDS 256

# define SIGCTX_PARENT 0
# define SIGCTX_CHILD 1
# define SIGCTX_HEREDOC 2

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}					t_token;

typedef struct s_command
{
	char			**cmd;

	int				infile_count;
	char			**infile;
	int				*is_heredoc;
	int				*in_quotes;

	int				outfile_count;
	char			**outfile;
	int				*is_append;
}					t_command;

typedef struct s_pipeline
{
	t_command		**commands;
	int				command_count;
}					t_pipeline;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	t_pipeline		*current_pipeline;
	t_env			*env_list;
	int				last_status;
	int				g_last_signal;
}					t_shell;

void				free_pipes(int **pipes, int size);

void				close_pipes_fds(int **pipes, int size);
int					**make_pipes(int n_pipes);
void				execute_cmd(t_shell *sh, int i, int **pipes, pid_t *pids);
char				*resolve_path(char *cmd, t_env *env_list);
int					execute_pipeline(t_shell *sh);
char				**convert_env_to_environ(t_env *env);
void				set_command_fds(t_shell *sh, int i, int **pipes);
void				free_and_close_all(t_pipeline *pipeline, int **pipes,
						int n_pipes);
void				set_signal(int flag);
// tmp
void				ft_echo(char **argv);
void				ft_cd(char **argv);
void				ft_pwd(char **argv);
void				ft_expor);
void				ft_unset(void);
void				ft_env(void);
void				ft_exit(void);

// handle_env.c
t_env				*copy_env(char **envp);
void				free_env_list(t_env *head);
// parse_line_utils.c
int					is_valid_quote(const char *str, int i);
int					is_space(char c);
t_command			*init_command(void);
// free_pipeline.c
void				free_command(t_command *cmd);
void				free_commands(t_command **commands, int command_count);
void				free_pipeline(t_pipeline *pipeline);
// parse_line.c
void				free_tokens(t_token **tokens, int token_count);
t_pipeline			*parse_line(const char *line, t_shell *shell);
// lexer.c
t_token				**lexer(const char *line, int *count);
// lexer_parse_redirect_token.c
t_token				*parse_redirect_token(const char *line, int *idx);
// lexer_parse_word_token.c
t_token				*parse_word_token(const char *line, int *i);
// check_syntax_errors.c
bool				check_syntax_errors(t_token **tokens, int count);
// check_syntax_errors_utils.c
void				print_syntax_error(const char *msg);
bool				is_redirect(t_token tok);
bool				is_pipe(t_token tok);
// change_tokens_to_commands.c
t_command			**change_tokens_to_commands(t_token **tokens,
						int *tok_count, int *cmd_count, t_shell *shell);
// set_cmds.c
void				set_cmd(t_command *command, const char *token_value,
						int *idx, t_shell *shell);
void				set_heredoc(t_command *command, const char *token_value,
						int *idx);
void				set_append(t_command *command, const char *token_value,
						int *idx);
void				set_outfile(t_command *command, const char *token_value,
						int *idx);
void				set_infile(t_command *command, const char *token_value,
						int *idx);
// set_cmds_utils.c
int					count_cmd(char **cmd);
char				*remove_quotes(const char *str);
char				*remove_quotes_with_flag(const char *str, int *quoted);
// expand_env.c
void				handle_normal_char(const char *str, int *i, char **buffer);
void				handle_dollar(const char *str, int *i, char **buffer,
						t_shell *shell);
char				*expand_env(const char *str, t_shell *shell);
// expand_var.c
char				*expand_var(const char *str, int *i, t_shell *shell);
char				*get_env_value(t_env *env, const char *key);
// str_appends.c
char				*str_append_str(char *s, const char *append);
char				*str_append_char(char *s, char c);
char				*str_append_except_for_quotes(char *buff, char *str,
						int *i);
t_command			**set_commands(const char *line, int *command_count,
						t_shell *shell);

#endif
