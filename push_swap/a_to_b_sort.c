/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:01:58 by shfujita          #+#    #+#             */
/*   Updated: 2025/07/26 15:05:50 by shfujita         ###   ########.fr       */
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
	int	ca;
	int	cb;

	ca = value->cost_a;
	cb = value->cost_b;
	while (ca > 0 && cb > 0)
	{
		rr_rotate(stack_a, stack_b);
		ca--;
		cb--;
	}
	while (ca < 0 && cb < 0)
	{
		rrr_rotate(stack_a, stack_b);
		ca++;
		cb++;
	}
}

void	ra_rra(t_stack **stack_a, t_stack *value)
{
	int	ca;
	int	cb;

	ca = value->cost_a;
	cb = value->cost_b;
	while (ca != 0)
	{
		if (ca > 0)
		{
			rotate(stack_a, 'a');
			ca--;
		}
		else
		{
			r_rotate(stack_a, 'a');
			ca++;
		}
	}
}

void	rb_rrb(t_stack **stack_b, t_stack *value)
{
	int	cb;

	cb = value->cost_b;
	while (cb != 0)
	{
		if (cb > 0)
		{
			rotate(stack_b, 'b');
			cb--;
		}
		else
		{
			r_rotate(stack_b, 'b');
			cb++;
		}
	}
}

void	a_to_b_sort(t_stack **stack_a, t_stack **stack_b, t_stack *value)
{
	rr_rrr(stack_a, stack_b, value);
	ra_rra(stack_a, value);
	rb_rrb(stack_b, value);
	push(stack_a, stack_b, 'a');
}
