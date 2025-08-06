/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:23:04 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/06 16:36:22 by shfujita         ###   ########.fr       */
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

int	find_min_data_pos(t_stack *stack)
{
	t_stack	*current;
	int		pos;
	int		min_pos;
	int		min_val;

	if (!stack)
		return (-1);
	current = stack;
	pos = 0;
	min_pos = 0;
	min_val = INT_MAX;
	while (1)
	{
		if (current->data < min_val)
		{
			min_val = current->data;
			min_pos = pos;
		}
		current = current->next;
		pos++;
		if (current == stack)
			break ;
	}
	return (min_pos);
}

void	move_to_b(t_stack **stack_a, t_stack **stack_b, int size)
{
	t_stack	*value;

	while (size > 3)
	{
		count_costs(*stack_a, *stack_b);
		value = find_min_cost(*stack_a);
		rotate_stack(stack_a, stack_b, value);
		push(stack_a, stack_b, 'b');
		size--;
	}
	sort_three_size_stack(stack_a);
}

void	move_to_a(t_stack **stack_a, t_stack **stack_b)
{
	int			pos;
	t_rota_cost	cost;

	if (!stack_b || !*stack_b)
		return ;
	while (*stack_b)
	{
		pos = get_insert_pos_to_a(*stack_a, (*stack_b)->data);
		cost = get_rotation_cost(pos, get_stack_size(*stack_a));
		while (cost.cost > 0)
		{
			if (cost.dir)
				rotate(stack_a, 'a');
			else
				r_rotate(stack_a, 'a');
			cost.cost--;
		}
		push(stack_b, stack_a, 'a');
	}
}

void	move_min_to_top(t_stack **stack_a)
{
	int			size;
	t_rota_cost	rota_cost;

	size = get_stack_size(*stack_a);
	rota_cost = get_rotation_cost(find_min_data_pos(*stack_a), size);
	while (rota_cost.cost--)
	{
		if (rota_cost.dir)
			rotate(stack_a, 'a');
		else
			r_rotate(stack_a, 'a');
	}
}
