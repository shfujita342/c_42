/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:35:12 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/06 21:03:56 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three_size_stack(t_stack **stack_a)
{
	int	first;
	int	second;
	int	third;

	if (get_stack_size(*stack_a) != 3)
		return ;
	first = (*stack_a)->data;
	second = (*stack_a)->next->data;
	third = (*stack_a)->next->next->data;
	if (first > second && second < third && first < third)
		swap_top(stack_a, 'a');
	else if (first > second && second > third)
	{
		swap_top(stack_a, 'a');
		r_rotate(stack_a, 'a');
	}
	else if (first < second && second > third && first < third)
	{
		swap_top(stack_a, 'a');
		rotate(stack_a, 'a');
	}
	else if (first < second && second > third && first > third)
		r_rotate(stack_a, 'a');
	else if (first > second && second < third && first > third)
		rotate(stack_a, 'a');
}

void	sort_four_size_stack(t_stack **stack_a, t_stack **stack_b)
{
	int	size_a;
	int	min_id;
	int	back;

	min_id = find_min_data_pos(*stack_a);
	size_a = get_stack_size(*stack_a);
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
	sort_three_size_stack(stack_a);
	push(stack_b, stack_a, 'a');
}

void	sort_five_size_stack(t_stack **stack_a, t_stack **stack_b)
{
	int	size_a;
	int	min_id;
	int	back;

	size_a = get_stack_size(*stack_a);
	min_id = find_min_data_pos(*stack_a);
	if (min_id <= size_a - min_id)
		while (min_id-- > 0)
			rotate(stack_a, 'a');
	else
	{
		back = size_a - min_id;
		while (back-- > 0)
			r_rotate(stack_a, 'a');
	}
	push(stack_a, stack_b, 'b');
	sort_four_size_stack(stack_a, stack_b);
	push(stack_b, stack_a, 'a');
}

void	sort_small_stack(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	size = get_stack_size(*stack_a);
	if (size == 2)
	{
		if ((*stack_a)->data > (*stack_a)->next->data)
			swap_top(stack_a, 'a');
	}
	else if (size == 3)
		sort_three_size_stack(stack_a);
	else if (size == 4)
		sort_four_size_stack(stack_a, stack_b);
	else if (size == 5)
		sort_five_size_stack(stack_a, stack_b);
}
