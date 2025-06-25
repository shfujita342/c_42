/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:20:04 by shfujita          #+#    #+#             */
/*   Updated: 2025/06/25 18:50:49 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	len(long n)
{
	int	res;

	res = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		res++;
	while (n)
	{
		res++;
		n /= 10;
	}
	return (res);
}

int	ft_put_nbr(int n)
{
	char	*s;
	int		res;

	s = ft_itoa(n);
	if (!s)
		return (-1);
	res = write(1, s, len(n));
	free(s);
	return (res);
}

char	*ft_uitoa(unsigned int n)
{
	int		length;
	char	*s;

	length = len(n);
	s = malloc(length + 1);
	if (!s)
		return (NULL);
	s[length] = '\0';
	while (length--)
	{
		s[length] = '0' + (n % 10);
		n /= 10;
	}
	return (s);
}

int	ft_put_unbr(unsigned int n)
{
	char	*s;
	int		res;

	s = ft_uitoa(n);
	if (!s)
		return (-1);
	res = write(1, s, len(n));
	free(s);
	return (res);
}
