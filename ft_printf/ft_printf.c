/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:05:23 by shfujita          #+#    #+#             */
/*   Updated: 2025/06/24 12:55:42 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_format(char c, va_list ap)
{
	if (c == 'c')
		return (ft_put_chr(va_arg(ap, int)));
	if (c == 's')
		return (ft_put_str(va_arg(ap, char *)));
	if (c == 'p')
		return (ft_put_ptr(va_arg(ap, void *)));
	if (c == 'd' || c == 'i')
		return (ft_put_nbr(va_arg(ap, int)));
	if (c == 'u')
		return (ft_put_unbr(va_arg(ap, unsigned int)));
	if (c == 'x')
		return (ft_put_hex((unsigned long)va_arg(ap, unsigned int), 0));
	if (c == 'X')
		return (ft_put_hex((unsigned long)va_arg(ap, unsigned int), 1));
	if (c == '%')
		return (ft_put_chr('%'));
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		printed;
	int		ret;

	if (!format)
		return (-1);
	va_start(ap, format);
	i = 0;
	printed = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			ret = print_format(format[++i], ap);
			if (ret < 0)
				return (va_end(ap), -1);
			printed += ret;
		}
		else
			printed += ft_put_chr(format[i]);
		i++;
	}
	va_end(ap);
	return (printed);
}
