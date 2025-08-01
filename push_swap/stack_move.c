/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:14:45 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/01 15:08:06 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_stack **from_stack, t_stack **to_stack, char which_stack)
{
	int	tmp;

	if (!from_stack || !*from_stack)
		return ;
	tmp = (*from_stack)->data;
	delete_node_top(from_stack);
	push_node(tmp, to_stack);
	if (which_stack == 'a')
		write(1, "pa\n", 3);
	else
		write(1, "pb\n", 3);
}

void	swap_top(t_stack **head, char which_stack)
{
	t_stack	*second;
	int		tmp;

	if (!head || !*head || ((*head)->next == *head))
		return ;
	second = (*head)->next;
	tmp = (*head)->data;
	(*head)->data = second->data;
	second->data = tmp;
	if (which_stack == 'a')
		write(1, "sa\n", 3);
	else if (which_stack == 'b')
		write(1, "sb\n", 3);
}
