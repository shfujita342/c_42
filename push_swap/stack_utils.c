/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:43:09 by shfujita          #+#    #+#             */
/*   Updated: 2025/06/25 19:43:35 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stack **head, char which_stack)
{
	if (!head || !*head || (*head)->next == *head)
		return ;
	*head = (*head)->next;
	if (which_stack == 'a')
		write(1, "ra", 2);
	else if (which_stack == 'b')
		write(1, "rb", 2);
	else
		write(1, "rr", 2);
}

void	r_rotate(t_stack **head, char which_stack)
{
	if (!head || !*head || (*head)->next == *head)
		return ;
	*head = (*head)->prev;
	if (which_stack == 'a')
		write(1, "rra", 3);
	else if (which_stack == 'b')
		write(1, "rrb", 3);
	else
		write(1, "rrr", 3);
}

void	push(t_stack **from_stack, t_stack **to_stack, char which_stack)
{
	int	tmp;

	if (!from_stack || !*from_stack || !to_stack || !*to_stack)
		tmp = (*from_stack)->data;
	delete (from_stack);
	insert(tmp, to_stack);
	if (which_stack == 'a')
		write(1, "pa", 2);
	else
		write(1, "pb", 2);
}

void	swap_top(t_stack **head, char which_stack)
{
	t_stack	*second;
	int		tmp;

	second = (*head)->next;
	if (!head || !*head || ((*head)->next == *head))
		return ;
	tmp = (*head)->data;
	(*head)->data = second->data;
	second->data = tmp;
	if (which_stack == 'a')
		write(1, "sa", 2);
	else if (which_stack == 'b')
		write(1, "sb", 2);
	else
		write(1, "ss", 2);
}
