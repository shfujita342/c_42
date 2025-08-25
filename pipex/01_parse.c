/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:10:29 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/25 17:11:57 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	free_strv(char **strv)
{
	int	i;

	if (!strv)
		return ;
	i = 0;
	while (strv[i])
	{
		free(strv[i]);
		i++;
	}
	free(strv);
}

void	free_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->cmd1)
		free_strv(pipex->cmd1);
	if (pipex->cmd2)
		free_strv(pipex->cmd2);
	free(pipex);
}

t_pipex	*parse_args(int argc, char *argv[])
{
	t_pipex	*res;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(1);
	}
	res = malloc(sizeof(t_pipex));
	if (!res)
		exit(1);
	res->infile = argv[1];
	res->outfile = argv[4];
	res->cmd1 = ft_split(argv[2], ' ');
	res->cmd2 = ft_split(argv[3], ' ');
	if (!res->cmd1 || !res->cmd2)
	{
		free_pipex(res);
		exit(1);
	}
	return (res);
}
