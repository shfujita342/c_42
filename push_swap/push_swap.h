/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:00:45 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/06 21:02:27 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

// # include "libft.h"
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_rota_cost
{
	int				cost;
	int				dir;
}					t_rota_cost;

typedef struct s_stack
{
	int				data;
	t_rota_cost		rota_cost_a;
	t_rota_cost		rota_cost_b;
	int				total_cost;
	struct s_stack	*prev;
	struct s_stack	*next;
}					t_stack;

t_rota_cost			get_rotation_cost(int index, int size);
int					get_total_cost(t_rota_cost *rota_cost_a,
						t_rota_cost *rota_cost_b);
int					get_insert_pos_to_b(t_stack *stack_b, int value);
int					get_insert_pos_to_a(t_stack *stack_a, int value);
void				count_costs(t_stack *from_stack, t_stack *to_stack);

void				move_to_b(t_stack **stack_a, t_stack **stack_b, int size);
void				move_to_a(t_stack **stack_a, t_stack **stack_b);
void				move_min_to_top(t_stack **stack_a);
t_stack				*parse_args(int argc, char *argv[]);
void				rotate_stack(t_stack **stack_a, t_stack **stack_b,
						t_stack *value);
void				sort_small_stack(t_stack **stack_a, t_stack **stack_b);
void				sort_three_size_stack(t_stack **stack_a);
void				sort(t_stack **stack_a, t_stack **stack_b);
void				push(t_stack **from_stack, t_stack **to_stack,
						char which_stack);
void				swap_top(t_stack **head, char which_stack);
void				rotate(t_stack **head, char which_stack);
void				r_rotate(t_stack **head, char which_stack);
void				rr_rotate(t_stack **stack_a, t_stack **stack_b);
void				rrr_rotate(t_stack **stack_a, t_stack **stack_b);
int					get_stack_size(t_stack *head);
void				delete_node_top(t_stack **head);
void				insert_node(int value, t_stack **head);
int					find_min_data_pos(t_stack *stack);
void				free_stack(t_stack **stack_a);
#endif
