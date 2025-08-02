/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:00:45 by shfujita          #+#    #+#             */
/*   Updated: 2025/08/01 20:46:51 by shfujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				data;
	int				index;
	int				cost_a;
	int				cost_b;
	int				total_cost;
	struct s_stack	*prev;
	struct s_stack	*next;
}					t_stack;

typedef struct s_size
{
	int				size_a;
	int				size_b;
}					t_size;

t_stack				*find_min_cost(t_stack *stack_a);
void				rr_rrr(t_stack **stack_a, t_stack **stack_b,
						t_stack *value);
void				ra_rra(t_stack **stack_a, t_stack *value);
void				rb_rrb(t_stack **stack_b, t_stack *value);
void				a_to_b_sort(t_stack **stack_a, t_stack **stack_b);
int					find_min_pos(t_stack *stack_a);
void				min_to_top(t_stack **stack_a);
void				b_to_a_sort(t_stack **stack_a, t_stack **stack_b);
int					stack_size(t_stack *head);
int					rotation_cost(int index, int size);
int					total_cost(int cost_a, int cost_b);
int					insert_pos(t_stack *stack_b, int value);
void				count_costs_a_to_b(t_stack *stack_a, t_stack *stack_b);
void				error_exit(void);
int					check_dup(t_stack *stack, int value);
int					arg_to_int(const char *str, int *value);
t_stack				*parse_args(int argc, char *argv[]);
void				push(t_stack **from_stack, t_stack **to_stack,
						char which_stack);
void				swap_top(t_stack **head, char which_stack);
void				rotate(t_stack **head, char which_stack);
void				r_rotate(t_stack **head, char which_stack);
void				rr_rotate(t_stack **stack_a, t_stack **stack_b);
void				rrr_rotate(t_stack **stack_a, t_stack **stack_b);
t_stack				*create_node(int value);
void				push_node(int value, t_stack **head);
void				delete_node_top(t_stack **head);
void				three_sort(t_stack **stack_a);
void				small_size_sort(t_stack **stack_a, t_stack **stack_b);

#endif
