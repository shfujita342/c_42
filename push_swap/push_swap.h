/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:00:45 by shfujita          #+#    #+#             */
/*   Updated: 2025/06/24 12:45:51 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				data;
	struct s_stack	*prev;
	struct s_stack	*next;
	int				size;
}					t_stack;

typedef struct s_size
{
	int				size_a;
	int				size_b;
}					t_size;

t_stack				*create_node(int value);
void				delete_node(t_stack *node, t_stack *head);
void				insert_node(int value, t_stack *head);

#endif
