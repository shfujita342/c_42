/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:14:45 by shfujita          #+#    #+#             */
/*   Updated: 2025/07/26 18:45:13 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_stack **from_stack, t_stack **to_stack, char which_stack)
{
	int	tmp;

	if (!from_stack || !*from_stack || !to_stack || !*to_stack)
		tmp = (*from_stack)->data;
	delete_node_top(from_stack);
	push_node(tmp, to_stack);
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
