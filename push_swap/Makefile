# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/29 22:27:36 by shfujita          #+#    #+#              #
#    Updated: 2025/08/06 19:21:09 by shfujita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = push_swap
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
INCLUDES    = -I $(LIBFT_DIR)

SRCS = \
    count_costs.c        \
    main.c               \
    move_stack.c         \
    parse_args.c         \
    rotate_stack.c       \
    sort.c               \
    sort_small_stack.c   \
    stack.c              \
    stack_func_move.c    \
    stack_func_rotate.c


OBJS        = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)


$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) \
	    -L $(LIBFT_DIR) -lft \
	    -o $(NAME)


%.o: %.c push_swap.h $(LIBFT_DIR)/libft.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean


fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all
