/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:36:36 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/06 19:26:54 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	free_stack(t_stack **stack_a)
{
	if (!stack_a)
		return ;
	while (*stack_a)
		delete_node_top(stack_a);
}

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

int	convert_arg_to_int(const char *str, int *value)
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
	*value = (int)(num * sign);
	return (1);
}

t_stack	*parse_args(int argc, char *argv[])
{
	int		i;
	int		value;
	t_stack	*stack;

	value = 0;
	stack = NULL;
	if (argc < 2)
		return (NULL);
	i = argc - 1;
	while (i >= 1)
	{
		if (!convert_arg_to_int(argv[i], &value))
		{
			free_stack(&stack);
			error_exit();
		}
		if (!check_dup(stack, value))
		{
			free_stack(&stack);
			error_exit();
		}
		insert_node(value, &stack);
		i--;
	}
	return (stack);
}
