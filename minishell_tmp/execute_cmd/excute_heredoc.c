/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:38:05 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 19:09:41 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_expand_env(const char *str, t_shell *shell)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = malloc(1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (str[i])
	{
		if (str[i] == '$')
			handle_dollar(str, &i, &buffer, shell);
		else
			handle_normal_char(str, &i, &buffer);
	}
	return (buffer);
}

static char	*find_unique_heredoc_file(void)
{
	char	filename[256];
	int		i;
	char	*numstr;

	i = 0;
	while (1)
	{
		ft_strcpy(filename, "/tmp/heredoc_");
		numstr = ft_itoa(i);
		if (!numstr)
			return (NULL);
		ft_strcat(filename, numstr);
		free(numstr);
		strcat(filename, ".tmp");
		if (access(filename, F_OK) == -1)
		{
			return (ft_strdup(filename));
		}
		i++;
	}
}

static void	write_heredoc_line(int fd, char *line, int is_quoted,
		t_shell *shell)
{
	char	*expanded;
	char	*str_to_write;
	size_t	len;

	if (is_quoted)
		str_to_write = line;
	else
	{
		expanded = heredoc_expand_env(line, shell);
		if (!expanded)
			return ;
		str_to_write = expanded;
	}
	len = ft_strlen(str_to_write);
	write(fd, str_to_write, len);
	write(fd, "\n", 1);
	if (!is_quoted)
		free(expanded);
}

static void	process_heredoc_input(int fd, char *delim, int is_quoted,
		t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(fd, line, is_quoted, shell);
		free(line);
	}
}

int	execute_heredoc(char *delim, t_shell *shell, int is_quoted)
{
	int		fd;
	char	*filename;

	filename = find_unique_heredoc_file();
	if (!filename)
		return (-1);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("open heredoc read");
		free(filename);
		return (-1);
	}
	process_heredoc_input(fd, delim, is_quoted, shell);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open heredoc read");
		free(filename);
		return (-1);
	}
	free(filename);
	return (fd);
}
