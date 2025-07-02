/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:13:09 by shfujita          #+#    #+#             */
/*   Updated: 2025/06/25 19:41:33 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack	*set_stack_a(int argc, char **argv, t_stack *head)
{
	int		i;
	long	num;

	i = argc - 1;
	while (i > 0)
	{
		num = ft_atoi(argv[i]);
		if (num > INT_MAX || num < INT_MIN)
			return (NULL);
		insert_nord(num, head);
		i--;
	}
	return (head);
}

static t_stack	*set_stack_b(t_stack *stack_a, t_stack *stack_b)
{
	if (!stack_a || stack_a->next == stack_a)
		return (NULL);
	push(stack_a, stack_b, 'b');
	push(stack_a, stack_b, 'b');
	if ((stack_b->data) < (stack_b->next->data))
		swap(stack_b, 'b');
	return (stack_b);
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		size_stack_a;
	int		size_stack_b;

	size_stack_a = argc - 1;
	size_stack_b = 2;
	stack_a = set_stack_a(argc, **argv, NULL);
	stack_b = set_stack_b(stack_a, stack_b);
	if (!stack_a)
	{
		write(1, "Error\n", 6);
		return (1);
	}
}
