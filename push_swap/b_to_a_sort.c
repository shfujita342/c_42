/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:30:34 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/01 18:00:49 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// int	find_min_index(t_stack *stack_a)
// {
// 	int		res;
// 	t_stack	*current;

// 	res = 0;
// 	current = stack_a;
// 	while (1)
// 	{
// 		if (current->index == 0)
// 			return (res);
// 		current = current->next;
// 		res++;
// 		if (current == stack_a)
// 			break ;
// 	}
// 	return (-1);
// }

int	find_min_pos(t_stack *stack)
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

void	min_to_top(t_stack **stack_a)
{
	int	size;
	int	cost;

	size = stack_size(*stack_a);
	cost = rotation_cost(find_min_pos(*stack_a), size);
	if (cost > 0)
		while (cost--)
			rotate(stack_a, 'a');
	else
		while (cost++)
			r_rotate(stack_a, 'a');
}

int	insert_pos_b_to_a(t_stack *stack_a, int value)
{
	t_stack	*current;
	int		pos;

	pos = 0;
	current = stack_a;
	while (1)
	{
		if (current->data > current->next->data)
		{
			if (current->next->data > value)
				return (pos + 1);
		}
		else if (current->data < value && value < current->next->data)
			return (pos + 1);
		pos++;
		current = current->next;
		if (current == stack_a)
			break ;
	}
	return (0);
}

void	b_to_a_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	size_a;
	int	cost;
	int	pos;

	if (!*stack_b)
		return ;
	size_a = stack_size(*stack_a);
	while (*stack_b)
	{
		pos = insert_pos_b_to_a(*stack_a, (*stack_b)->data);
		cost = rotation_cost(pos, size_a);
		if (cost > 0)
			while (cost-- > 0)
				rotate(stack_a, 'a');
		else
			while (cost++ < 0)
				r_rotate(stack_a, 'a');
		push(stack_b, stack_a, 'a');
		size_a++;
	}
	min_to_top(stack_a);
}
