/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:01:48 by shfujita          #+#    #+#             */
/*   Updated: 2025/06/23 17:07:34 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	psw_atoi(char *str)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num * sign);
}

long	parse(char *str)
{
	int		i;
	long	num;

	i = 0;
	if (!str)
		return (INT_MAX + 1);
	if (str[i] == '-')
		i++;
	if (!str[i])
		return (INT_MAX + 1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (INT_MAX + 1);
		i++;
	}
	num = ft_atoi(str);
	return (num);
}
