/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_costs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:02:14 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/06 17:46:12 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_rota_cost	get_rotation_cost(int index, int size)
{
	t_rota_cost	value;

	if (index < size - index)
	{
		value.cost = index;
		value.dir = 1;
	}
	else
	{
		value.cost = size - index;
		value.dir = 0;
	}
	return (value);
}

int	get_total_cost(t_rota_cost *rota_cost_a, t_rota_cost *rota_cost_b)
{
	if (rota_cost_a->dir == rota_cost_b->dir)
	{
		if (rota_cost_a->cost >= rota_cost_b->cost)
			return (rota_cost_a->cost);
		else
			return (rota_cost_b->cost);
	}
	else
		return (rota_cost_a->cost + rota_cost_b->cost);
}

int	get_insert_pos_to_b(t_stack *stack_b, int value)
{
	t_stack	*current;
	int		pos;

	if (!stack_b)
		return (0);
	pos = 0;
	current = stack_b;
	while (1)
	{
		if (current->data < current->next->data)
		{
			if (current->data > value || current->next->data < value)
				return (pos + 1);
		}
		else if (current->data > value && value > current->next->data)
			return (pos + 1);
		pos++;
		current = current->next;
		if (current == stack_b)
			break ;
	}
	return (0);
}

int	get_insert_pos_to_a(t_stack *stack_a, int value)
{
	t_stack	*current;
	int		pos;

	if (!stack_a)
		return (0);
	pos = 0;
	current = stack_a;
	while (1)
	{
		if (current->data > current->next->data)
		{
			if (current->data < value || current->next->data > value)
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

void	count_costs(t_stack *from_stack, t_stack *to_stack)
{
	int		size_from;
	int		size_to;
	int		id_from;
	int		id_to;
	t_stack	*current;

	if (!from_stack)
		return ;
	current = from_stack;
	id_from = 0;
	size_from = get_stack_size(from_stack);
	size_to = get_stack_size(to_stack);
	while (1)
	{
		id_to = get_insert_pos_to_b(to_stack, current->data);
		current->rota_cost_a = get_rotation_cost(id_from, size_from);
		current->rota_cost_b = get_rotation_cost(id_to, size_to);
		current->total_cost = get_total_cost(&current->rota_cost_a,
				&current->rota_cost_b);
		current = current->next;
		id_from++;
		if (current == from_stack)
			break ;
	}
}
