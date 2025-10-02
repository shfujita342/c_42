/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:06:39 by yseto             #+#    #+#             */
/*   Updated: 2025/09/30 21:10:25 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_putchar(char c);
int	ft_putstr(const char *s);
int	ft_putnbr(long int n);
int	ft_putnbr_unsigned(unsigned int n);
int	ft_puthex(unsigned int n, char uppercase);
int	ft_puthex_ulong(unsigned long n, char uppercase);
int	ft_putptr(void *ptr);
int	ft_printf(const char *format, ...);

#endif
