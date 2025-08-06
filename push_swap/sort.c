/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:20:03 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/06 17:43:44 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	t_stack	*current;
	int		size;

	size = get_stack_size(stack);
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

void	set_stack_b(t_stack **stack_a, t_stack **stack_b, int size)
{
	if (size >= 6)
	{
		push(stack_a, stack_b, 'b');
		push(stack_a, stack_b, 'b');
	}
}

void	sort(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	if (is_sorted(*stack_a))
		return ;
	size = get_stack_size(*stack_a);
	if (size <= 5)
	{
		sort_small_stack(stack_a, stack_b);
		move_min_to_top(stack_a);
		return ;
	}
	set_stack_b(stack_a, stack_b, size);
	move_to_b(stack_a, stack_b, size);
	move_to_a(stack_a, stack_b);
	move_min_to_top(stack_a);
}
