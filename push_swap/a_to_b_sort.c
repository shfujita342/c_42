/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:01:58 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/01 14:57:43 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*find_min_cost(t_stack *stack_a)
{
	t_stack	*current;
	t_stack	*min;

	if (!stack_a)
		return (NULL);
	current = stack_a->next;
	min = stack_a;
	while (current != stack_a)
	{
		if (min->total_cost > current->total_cost)
			min = current;
		current = current->next;
	}
	return (min);
}

void	rr_rrr(t_stack **stack_a, t_stack **stack_b, t_stack *value)
{
	while (value->cost_a > 0 && value->cost_b > 0)
	{
		rr_rotate(stack_a, stack_b);
		value->cost_a--;
		value->cost_b--;
	}
	while (value->cost_a < 0 && value->cost_b < 0)
	{
		rrr_rotate(stack_a, stack_b);
		value->cost_a++;
		value->cost_b++;
	}
}

void	ra_rra(t_stack **stack_a, t_stack *value)
{
	while (value->cost_a != 0)
	{
		if (value->cost_a > 0)
		{
			rotate(stack_a, 'a');
			value->cost_a--;
		}
		else
		{
			r_rotate(stack_a, 'a');
			value->cost_a++;
		}
	}
}

void	rb_rrb(t_stack **stack_b, t_stack *value)
{
	while (value->cost_b != 0)
	{
		if (value->cost_b > 0)
		{
			rotate(stack_b, 'b');
			value->cost_b--;
		}
		else
		{
			r_rotate(stack_b, 'b');
			value->cost_b++;
		}
	}
}

void	a_to_b_sort(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*value;

	value = find_min_cost(*stack_a);
	rr_rrr(stack_a, stack_b, value);
	ra_rra(stack_a, value);
	rb_rrb(stack_b, value);
	push(stack_a, stack_b, 'b');
}
