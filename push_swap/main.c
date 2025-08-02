/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:13:09 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/02 16:48:49 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	free_stack(t_stack **stack_a)
{
	if (!stack_a)
		return ;
	while (*stack_a)
		delete_node_top(stack_a);
}

static int	is_sorted(t_stack *stack)
{
	t_stack	*current;
	int		size;

	size = stack_size(stack);
	if (!stack || size < 2)
		return (1);
	current = stack;
	size--;
	while (size--)
	{
		if (current->data > current->next->data)
			return (0);
		current = current->next;
	}
	return (1);
}

static void	set_stack_b(t_stack **stack_a, t_stack **stack_b, int size)
{
	if (size >= 6)
	{
		push(stack_a, stack_b, 'b');
		push(stack_a, stack_b, 'b');
	}
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = parse_args(argc, argv);
	stack_b = NULL;
	if (is_sorted(stack_a))
	{
		free_stack(&stack_a);
		return (0);
	}
	set_stack_b(&stack_a, &stack_b, stack_size(stack_a));
	if (stack_size(stack_a) <= 5)
		small_size_sort(&stack_a, &stack_b);
	while (stack_size(stack_a) > 3)
	{
		count_costs_a_to_b(stack_a, stack_b);
		a_to_b_sort(&stack_a, &stack_b);
	}
	if (stack_size(stack_a) == 3)
		three_sort(&stack_a);
	b_to_a_sort(&stack_a, &stack_b);
	free_stack(&stack_a);
	return (0);
}
