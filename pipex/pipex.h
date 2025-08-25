/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fujit <fujit@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:05:09 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/25 06:25:40 by fujit            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	int		infd;
	int		outfd;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
}			t_pipex;

t_pipex		*parse_args(int argc, char *argv[]);
int			execute_pipex(t_pipex *pipex, char *envp[]);
pid_t		make_child_process_cmd1(t_pipex *pipex);
pid_t		make_child_process_cmd2(t_pipex *pipex);
void		free_pipex(t_pipex *pipex);
void		free_strv(char **strv);
char		*resolve_path(char *cmd, char *envp[]);
void		is_ok(int res, t_pipex *p);
void		close_fds(t_pipex *pipex);
void		free_strv(char **strv);
void	print_errno2(const char *pfx, const char *name);
#endif
