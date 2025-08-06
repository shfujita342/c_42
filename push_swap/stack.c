/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:13:40 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/05 21:41:14 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*create_node(int value)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->data = value;
	node->rota_cost_a.cost = 0;
	node->rota_cost_b.cost = 0;
	node->rota_cost_a.dir = 0;
	node->rota_cost_b.dir = 0;
	node->total_cost = 0;
	node->next = node;
	node->prev = node;
	return (node);
}

void	insert_node(int value, t_stack **head)
{
	t_stack	*node;
	t_stack	*tail;

	node = create_node(value);
	if (!node)
		return ;
	if (!*head)
		*head = node;
	else
	{
		tail = (*head)->prev;
		node->next = *head;
		node->prev = tail;
		(*head)->prev = node;
		tail->next = node;
		*head = node;
	}
}

void	delete_node_top(t_stack **head)
{
	t_stack	*prev;
	t_stack	*next;
	t_stack	*tmp;

	if (!head || !*head)
		return ;
	tmp = *head;
	if (tmp->next == tmp)
	{
		free(tmp);
		*head = NULL;
	}
	else
	{
		prev = tmp->prev;
		next = tmp->next;
		prev->next = next;
		next->prev = prev;
		*head = next;
		free(tmp);
	}
}

int	get_stack_size(t_stack *head)
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
