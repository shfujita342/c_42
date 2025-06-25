/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:48:21 by shfujita          #+#    #+#             */
/*   Updated: 2025/05/19 13:51:57 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define BASE "0123456789abcdef"
# define BASE_UP "0123456789ABCDEF"

# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_put_chr(int c);
int	ft_put_str(const char *s);
int	ft_put_ptr(void *p);
int	ft_put_nbr(int n);
int	ft_put_unbr(unsigned int n);
int	ft_put_hex(unsigned long n, int upper);

#endif
