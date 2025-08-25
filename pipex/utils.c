/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fujit <fujit@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 06:21:26 by fujit             #+#    #+#             */
/*   Updated: 2025/08/25 06:34:56 by fujit            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	print_errno2(const char *pfx, const char *name)
{
	char	*msg1;
	char	*msg2;
	char	*msg3;
	char	*full;

	msg1 = ft_strjoin(pfx, ": ");
	msg2 = ft_strjoin(msg1, name);
	free(msg1);
	msg3 = ft_strjoin(msg2, ": ");
	free(msg2);
	full = ft_strjoin(msg3, strerror(errno));
	free(msg3);
	msg1 = ft_strjoin(full, "\n");
	free(full);
	if (!msg1)
		return ;
	write(2, msg1, strlen(msg1));
	free(msg1);
}