/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:13:09 by shfujita          #+#    #+#             */
/*   Updated: 2025/07/28 20:44:02 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*bubble_sort(int *value, int size)
{
	int	i;
	int	j;
	int	tmp;

	if (!value)
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (value[i] > value[j])
			{
				tmp = value[i];
				value[i] = value[j];
				value[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (value);
}

int	*stack_to_array(t_stack *stack)
{
	int		size;
	int		*array;
	int		i;
	t_stack	*current;

	current = stack;
	i = 0;
	size = stack_size(stack);
	array = malloc(sizeof(int) * size);
	if (!array)
		return (NULL);
	while (i < size)
	{
		array[i] = current->data;
		current = current->next;
		i++;
	}
	return (array);
}

static void	assign_index(t_stack *stack_a)
{
	int		size;
	int		*array;
	int		rank;
	int		i;
	t_stack	*current;

	if (!stack_a)
		return ;
	i = 0;
	size = stack_size(stack_a);
	array = bubble_sort(stack_to_array(stack_a), size);
	if (!array)
		return ;
	current = stack_a;
	while (i < size)
	{
		rank = 0;
		while (rank < size && array[rank] != current->data)
			rank++;
		current->index = rank;
		current = current->next;
	}
	free(array);
}

int	main(int argc, char *argv[])
{
}
