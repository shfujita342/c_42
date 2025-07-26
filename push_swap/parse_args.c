/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:36:36 by shfujita          #+#    #+#             */
/*   Updated: 2025/07/26 17:36:39 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_exit(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int	check_dup(t_stack *stack, int value)
{
	t_stack	*current;

	if (!stack)
		return (1);
	current = stack;
	while (1)
	{
		if (current->data == value)
			return (0);
		current = current->next;
		if (current == stack)
			break ;
	}
	return (1);
}

int	arg_to_int(const char *str, int *res)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
	if (!str || !*str)
		return (0);
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		num = num * 10 + (*str - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && -1 * num < INT_MIN))
			return (0);
		str++;
	}
	*res = (int)(num * sign);
	return (1);
}

t_stack	*parse_args(int argc, char *argv[], t_stack **stack_a)
{
	int		i;
	long	value;
	t_stack	*stack;

	stack = NULL;
	if (argc < 2)
		return (NULL);
	i = argc - 1;
	while (i >= 0)
	{
		if (!arg_to_int(argv[i], &value))
			error_exit();
		if (!check_dup(stack, (int)value))
			error_exit();
		push_node(value, stack_a);
		i--;
	}
	return (stack);
}
