/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_chr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:25:14 by shfujita          #+#    #+#             */
/*   Updated: 2025/05/18 18:30:42 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_chr(int c)
{
	return (write(1, &c, 1));
}

int	ft_put_str(const char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[len])
		len++;
	return (write(1, s, len));
}
