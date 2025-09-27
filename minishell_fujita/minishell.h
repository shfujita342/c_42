/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:57:00 by yseto             #+#    #+#             */
/*   Updated: 2025/09/22 17:13:38 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define MAX_ARGS 256
# define MAX_COMMANDS 256

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

	int				num_infd;
	int				num_outfd;
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

// handle_env_list.c
t_env				*copy_env(char **envp);
void				free_env_list(t_env *head);
// free_pipeline.c
void				free_command(t_command *cmd);
void				free_pipeline(t_pipeline *pipeline);
// parse_line.c
t_pipeline			*parse_line(const char *line, t_shell *shell);
// parse_command.c
t_command			*parse_command(char *cmd_str, t_env *env_list);
// parse_command_utils.c
int					is_space(char c);
int					is_valid_quote(const char *str, int i);
// parse_redirect.c
void				parse_redirect(t_command *cmd, char *str, int *i);
// parse_token.c
char				*parse_token(const char *str, int *i, t_env *env);
// parse_token_utils.c
char				*get_env_value(t_env *env, const char *key);
char				*expand_var(const char *str, int *i, t_env *env);
// str_append.c
char				*str_append_except_for_quotes(char *buff, char *str,
						int *i);
char				*str_append_str(char *s, const char *append);
char				*str_append_char(char *s, char c);

#endif
