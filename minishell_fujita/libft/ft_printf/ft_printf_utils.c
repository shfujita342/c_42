/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:42:56 by yseto             #+#    #+#             */
/*   Updated: 2025/05/22 21:07:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(long int n)
{
	int	count;
	int	ret;

	count = 0;
	if (n < 0)
	{
		ret = ft_putchar('-');
		if (ret == -1)
			return (-1);
		n *= -1;
		count += ret;
	}
	if (n >= 10)
	{
		ret = ft_putnbr(n / 10);
		if (ret == -1)
			return (-1);
		count += ret;
	}
	ret = ft_putchar((n % 10) + '0');
	if (ret == -1)
		return (-1);
	count += ret;
	return (count);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int	count;
	int	ret;

	count = 0;
	if (n >= 10)
	{
		ret = ft_putnbr_unsigned(n / 10);
		if (ret == -1)
			return (-1);
		count += ret;
	}
	ret = ft_putchar((n % 10) + '0');
	if (ret == -1)
		return (-1);
	count += ret;
	return (count);
}

int	ft_puthex(unsigned int n, char uppercase)
{
	int		count;
	int		ret;
	char	*base;

	count = 0;
	if (uppercase == 'x')
		base = "0123456789abcdef";
	else
	{
		base = "0123456789ABCDEF";
	}
	if (n >= 16)
	{
		ret = ft_puthex(n / 16, uppercase);
		if (ret == -1)
			return (-1);
		count += ret;
	}
	ret = ft_putchar(base[n % 16]);
	if (ret == -1)
		return (-1);
	count += ret;
	return (count);
}

int	ft_puthex_ulong(unsigned long n, char uppercase)
{
	int		count;
	int		ret;
	char	*base;

	count = 0;
	if (uppercase == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		ret = ft_puthex_ulong(n / 16, uppercase);
		if (ret == -1)
			return (-1);
		count += ret;
	}
	ret = ft_putchar(base[n % 16]);
	if (ret == -1)
		return (-1);
	count += ret;
	return (count);
}

int	ft_putptr(void *ptr)
{
	int	count;
	int	ret;

	if (ptr == NULL)
		return (ft_putstr("(nil)"));
	count = 0;
	ret = ft_putstr("0x");
	if (ret == -1)
		return (-1);
	count += ret;
	ret = ft_puthex_ulong((unsigned long)ptr, 'x');
	if (ret == -1)
		return (-1);
	count += ret;
	return (count);
}
