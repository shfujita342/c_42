/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:12:54 by yseto             #+#    #+#             */
/*   Updated: 2025/09/30 21:09:31 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(const char *s)
{
	int	count;
	int	ret;

	count = 0;
	if (!s)
		s = "(null)";
	while (*s)
	{
		ret = ft_putchar(*s++);
		if (ret == -1)
			return (-1);
		count += ret;
	}
	return (count);
}

static int	handle_format(char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (specifier == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (specifier == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (specifier == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	else if (specifier == 'x')
		return (ft_puthex(va_arg(args, int), 'x'));
	else if (specifier == 'X')
		return (ft_puthex(va_arg(args, int), 'X'));
	else if (specifier == '%')
		return (ft_putchar('%'));
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	int		ret;
	va_list	args;

	if (!format)
		return (-1);
	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
			ret = handle_format(*(++format), args);
		else
			ret = ft_putchar(*format);
		if (ret == -1)
			return (va_end(args), -1);
		count += ret;
		format++;
	}
	return (va_end(args), count);
}

// #include <stdio.h> // 標準 printf 用

// int	main(void)
// {
// 	int		len;
// 	void	*p;

// 	p = 0;
// 	len = printf("%p,%p", p, p);
// 	printf("%d", len);
// 	len = ft_printf("%p,%p", p, p);
// 	ft_printf("%d", len);
// 	return (0);
// }
