/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:44:12 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/01 19:57:40 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stack **head, char which_stack)
{
	if (!head || !*head || (*head)->next == *head)
		return ;
	*head = (*head)->next;
	if (which_stack == 'a')
		write(1, "ra\n", 3);
	else
		write(1, "rb\n", 3);
}

void	r_rotate(t_stack **head, char which_stack)
{
	if (!head || !*head || (*head)->next == *head)
		return ;
	*head = (*head)->prev;
	if (which_stack == 'a')
		write(1, "rra\n", 4);
	else
		write(1, "rrb\n", 4);
}

void	rr_rotate(t_stack **stack_a, t_stack **stack_b)
{
	if (!stack_a || !*stack_a || (*stack_a)->next == *stack_a || !stack_b
		|| !*stack_b || (*stack_b)->next == *stack_b)
		return ;
	*stack_a = (*stack_a)->next;
	*stack_b = (*stack_b)->next;
	write(1, "rr\n", 3);
}

void	rrr_rotate(t_stack **stack_a, t_stack **stack_b)
{
	if (!stack_a || !*stack_a || (*stack_a)->next == *stack_a || !stack_b
		|| !*stack_b || (*stack_b)->next == *stack_b)
		return ;
	*stack_a = (*stack_a)->prev;
	*stack_b = (*stack_b)->prev;
	write(1, "rrr\n", 4);
}
