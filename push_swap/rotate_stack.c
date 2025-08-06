/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:00:45 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/06 17:59:24 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exe_rr_or_rrr(t_stack **stack_a, t_stack **stack_b, t_stack *value)
{
	if (value->rota_cost_a.dir != value->rota_cost_b.dir)
		return ;
	while (value->rota_cost_a.cost > 0 && value->rota_cost_b.cost > 0)
	{
		if (value->rota_cost_a.dir)
			rr_rotate(stack_a, stack_b);
		else
			rrr_rotate(stack_a, stack_b);
		value->rota_cost_a.cost--;
		value->rota_cost_b.cost--;
	}
}

void	exe_ra_or_rra(t_stack **stack_a, t_stack *value)
{
	while (value->rota_cost_a.cost > 0)
	{
		if (value->rota_cost_a.dir)
			rotate(stack_a, 'a');
		else
			r_rotate(stack_a, 'a');
		value->rota_cost_a.cost--;
	}
}

void	exe_rb_or_rrb(t_stack **stack_b, t_stack *value)
{
	while (value->rota_cost_b.cost > 0)
	{
		if (value->rota_cost_b.dir)
			rotate(stack_b, 'b');
		else
			r_rotate(stack_b, 'b');
		value->rota_cost_b.cost--;
	}
}

void	rotate_stack(t_stack **stack_a, t_stack **stack_b, t_stack *value)
{
	exe_rr_or_rrr(stack_a, stack_b, value);
	exe_ra_or_rra(stack_a, value);
	exe_rb_or_rrb(stack_b, value);
}
