/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:30:34 by shfujita          #+#    #+#             */
/*   Updated: 2025/07/29 22:37:28 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_id(t_stack *stack_a)
{
	int		res;
	t_stack	*current;

	res = 0;
	current = stack_a;
	while (1)
	{
		if (current->index == 0)
			return (res);
		current = current->next;
		res++;
		if (current == stack_a)
			break ;
	}
	return (-1);
}

void	min_to_top(t_stack **stack_a)
{
	int	size;
	int	cost;

	size = stack_size(*stack_a);
	cost = rotation_cost(find_min_id(*stack_a), size);
	if (cost > 0)
		while (cost--)
			rotate(stack_a, 'a');
	else
		while (cost++)
			r_rotate(stack_a, 'a');
}

void	b_to_a_sort(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*current;
	int		size;
	int		cost;

	current = *stack_b;
	while (1)
	{
		size = stack_size(*stack_b);
		cost = rotation_cost(insert_pos(*stack_a, current->data), size);
		if (cost > 0)
			while (cost--)
				rotate(stack_a, 'a');
		else
			while (cost++)
				r_rotate(stack_a, 'a');
		push(stack_b, stack_a, 'a');
		current = current->next;
		if (current == *stack_a)
			break ;
	}
	min_to_top(stack_a);
}
