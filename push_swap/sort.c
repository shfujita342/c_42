/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:57:10 by shfujita          #+#    #+#             */
/*   Updated: 2025/07/25 14:56:14 by shfujita         ###   ########.fr       */
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
	if (index <= size / 2)
		return (index);
	else
		return (-(index - size));
}

int	total_cost(int cost_a, int cost_b)
{
	if (cost_a == cost_b)
	{
		if (cost_a < 0)
		{
			cost_a *= -1;
			cost_b *= -1;
		}
		if (cost_a > cost_b)
			return (cost_a);
		else
			return (cost_b);
	}
	else
	{
		if (cost_a < 0)
			cost_a *= -1;
		if (cost_b < 0)
			cost_b *= -1;
		return (cost_a + cost_b);
	}
}

int	insert_pos(t_stack *stack_b, int value)
{
	t_stack	*current;
	int		pos;

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

void	count_costs(t_stack *stack_a, t_stack *stack_b)
{
	int size_a;
	int size_b;
	int id_a;
	int id_b;
	t_stack *current_a;

	if (!stack_a || !stack_b)
		return ;
	current_a = stack_a;
	id_a = 0;
	size_a = stack_size(stack_a);
	size_b = stack_size(stack_b);
	while (1)
	{
		current_a->cost_a = rotation_cost(id_a, size_a);
		id_b = insert_pos(stack_b, current_a->data);
		current_a->cost_b = rotation_cost(id_b, size_b);
		current_a->total_cost = total_cost(current_a->cost_a,
				current_a->cost_b);
		current_a = current_a->next;
		id_a++;
		if (current_a == stack_a)
			break ;
	}
}
