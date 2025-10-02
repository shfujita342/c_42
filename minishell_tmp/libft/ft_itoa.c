/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:31:53 by yseto             #+#    #+#             */
/*   Updated: 2025/10/01 11:34:30 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_digits(long num)
{
	int	cd;

	cd = 0;
	if (num <= 0)
		cd = 1;
	while (num != 0)
	{
		num /= 10;
		cd++;
	}
	return (cd);
}

static void	convert_number(char *s_num, long num, int len)
{
	int	is_neg;

	is_neg = 0;
	if (num < 0)
	{
		is_neg = 1;
		num = -num;
		s_num[0] = '-';
	}
	if (num == 0)
	{
		s_num[0] = '0';
		return ;
	}
	while (num > 0)
	{
		s_num[--len] = '0' + (num % 10);
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	long	num;
	int		len;
	char	*s_num;

	num = n;
	len = count_digits(num);
	s_num = malloc(len + 1);
	if (!s_num)
		return (NULL);
	s_num[len] = '\0';
	convert_number(s_num, num, len);
	return (s_num);
}

// int	main(void)
// {
// 	int		n;
// 	char	*s_num;

// 	n = 0;
// 	s_num = ft_itoa(n);
// 	printf("%s", s_num);
// 	return (0);
// }
