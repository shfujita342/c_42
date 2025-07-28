/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_size_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:35:12 by shfujita          #+#    #+#             */
/*   Updated: 2025/07/28 16:35:31 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_id(t_stack *stack_a)
{
	t_stack	*current;
	int		min_data;
	int		idx;
	int		min_idx;

	if (!stack_a)
		return (-1);
	idx = 0;
	min_idx = 0;
	current = stack_a;
	min_data = current->data;
	while (1)
	{
		if (current->data < min_data)
		{
			min_idx = idx;
			min_data = current->data;
		}
		idx++;
		current = current->next;
		if (current == stack_a)
			break ;
	}
	return (min_idx);
}

void	three_sort(t_stack **stack_a)
{
	int	first;
	int	second;
	int	third;

	first = (*stack_a)->data;
	second = (*stack_a)->next->data;
	third = (*stack_a)->next->next->data;
	if (first > second && second < third && first < third)
		swap_head(stack_a, 'a');
	else if (first > second && second > third)
	{
		swap_head(stack_a, 'a');
		r_rotate(stack_a, 'a');
	}
	else if (first < second && second > third && first < third)
	{
		swap_head(stack_a, 'a');
		rotate(stack_a, 'a');
	}
	else if (first < second && second > third && first > third)
		r_rotate(stack_a, 'a');
	else if (first > second && second < third && first > third)
		rotate(stack_a, 'a');
}

void	four_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	size_a;
	int	min_id;
	int	back;

	min_id = find_min_id(*stack_a);
	size_a = stack_size(*stack_a);
	if (min_id <= size_a / 2)
		while (min_id-- > 0)
			rotate(stack_a, 'a');
	else
	{
		back = size_a - min_id;
		while (back-- > 0)
			r_rotate(stack_a, 'a');
	}
	push(stack_a, stack_b, 'b');
	three_sort(stack_a);
	push(stack_b, stack_a, 'a');
}

void	five_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	size_a;
	int	min_id;
	int	back;

	size_a = stack_size(*stack_a);
	min_id = find_min_id(*stack_a);
	if (min_id <= size_a / 2)
		while (min_id-- > 0)
			rotate(stack_a, 'a');
	else
	{
		back = size_a - min_id;
		while (back-- > 0)
			r_rotate(stack_a, 'a');
	}
	push(stack_a, stack_b, 'b');
	four_sort(stack_a, stack_b);
	push(stack_b, stack_a, 'a');
}
