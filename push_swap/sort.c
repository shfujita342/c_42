/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:57:10 by shfujita          #+#    #+#             */
/*   Updated: 2025/07/02 20:49:05 by shfujita         ###   ########.fr       */
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

int	move_count(t_stack *stack_a, t_stack *stack_b, int id)
{
	int	size;
	int	cnt;
	int	id_b;

	id_b = 0;
	size = stack_size(stack_a);
	if ((size - 1) - id > id)
		cnt = id;
	else
		cnt = (size - 1 - id);
	if (((stack_a->data) >= (stack_b->data))
		|| (stack_a->data) <= (stack_b->prev)->data)
		return (cnt);
	size = stack_size(stack_b);
	while ((stack_a->data) < (stack_b->data))
	{
		id_b++;
		stack_b = stack_b->next;
	}
	if ((size - 1 - id_b) > id_b)
		return (cnt + id_b);
	else
		return (cnt + (size - 1 - id_b));
}
