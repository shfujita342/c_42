/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:59:23 by yseto             #+#    #+#             */
/*   Updated: 2025/09/30 21:03:04 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	ft_fputc(int c, FILE *stream)
{
	if (!stream)
		return (EOF);
	if (write(fileno(stream), &c, 1) == 1)
		return ((unsigned char)c);
	else
		return (EOF);
}

int	putchar_file(FILE *stream, char c)
{
	if (ft_fputc(c, stream) != EOF)
		return (1);
	else
		return (-1);
}

int	putstr_file(FILE *stream, const char *s)
{
	int	len;

	len = 0;
	if (!s)
		s = "(null)";
	while (*s)
	{
		if (putchar_file(stream, *s++) < 0)
			return (-1);
		len++;
	}
	return (len);
}
