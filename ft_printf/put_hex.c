/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:27:49 by shfujita          #+#    #+#             */
/*   Updated: 2025/05/19 12:43:57 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_hex(unsigned long n, int upper)
{
	char	res[17];
	int		j;
	int		i;
	char	*base;

	j = 0;
	while (j < 17)
	{
		res[j] = 0;
		j++;
	}
	i = 16;
	res[i] = '\0';
	if (n == 0)
		return (write(1, "0", 1));
	if (upper)
		base = BASE_UP;
	else
		base = BASE;
	while (n)
	{
		res[--i] = base[n % 16];
		n /= 16;
	}
	return (write(1, &res[i], 16 - i));
}

int	ft_put_ptr(void *p)
{
	int	res;
	int	add;

	if (!p)
		return (write(1, "(nil)", 5));
	res = write(1, "0x", 2);
	if (res < 0)
		return (-1);
	add = ft_put_hex((unsigned long)p, 0);
	if (add < 0)
		return (-1);
	return (res + add);
}
