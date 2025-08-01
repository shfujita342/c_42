/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_costs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:02:14 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/01 14:47:09 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_size(t_stack *head)
{
	t_stack	*node;
	int		size;

	size = 1;
	if (!head)
		return (0);
	if (head->next == head)
		return (1);
	node = head->next;
	while (node != head)
	{
		size++;
		node = node->next;
	}
	return (size);
}

int	rotation_cost(int index, int size)
{
	if (index <= size - index)
		return (index);
	else
		return (-(size - index));
}

int	total_cost(int cost_a, int cost_b)
{
	if ((cost_a >= 0 && cost_b >= 0) || (cost_a < 0 && cost_b < 0))
	{
		if (cost_a < 0)
		{
			if (cost_a < cost_b)
				return (-cost_a);
			else
				return (-cost_b);
		}
		if (cost_a > cost_b)
			return (cost_a);
		else
			return (cost_b);
	}
	else
	{
		if (cost_a < 0)
			cost_a = -cost_a;
		if (cost_b < 0)
			cost_b = -cost_b;
		return (cost_a + cost_b);
	}
}

int	insert_pos(t_stack *stack_b, int value)
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

void	count_costs_a_to_b(t_stack *stack_a, t_stack *stack_b)
{
	int		size_a;
	int		size_b;
	int		id_a;
	int		id_b;
	t_stack	*current;

	if (!stack_a)
		return ;
	current = stack_a;
	id_a = 0;
	size_a = stack_size(stack_a);
	size_b = stack_size(stack_b);
	while (1)
	{
		current->cost_a = rotation_cost(id_a, size_a);
		id_b = insert_pos(stack_b, current->data);
		current->cost_b = rotation_cost(id_b, size_b);
		current->total_cost = total_cost(current->cost_a, current->cost_b);
		current = current->next;
		id_a++;
		if (current == stack_a)
			break ;
	}
}
