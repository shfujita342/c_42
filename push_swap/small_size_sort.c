/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_size_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:35:12 by shfujita          #+#    #+#             */
/*   Updated: 2025/07/26 19:53:18 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
