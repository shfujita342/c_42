# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/21 20:38:29 by shfujita          #+#    #+#              #
#    Updated: 2025/08/25 16:50:41 by shfujita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = pipex
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
INCLUDES    = -I $(LIBFT_DIR)

SRCS = \
    00_main.c    \
    01_parse.c\
	03_path.c\
	04_child_process.c\
	02_execute.c

OBJS        = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)


$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) \
	    -L $(LIBFT_DIR) -lft \
	    -o $(NAME)


%.o: %.c pipex.h $(LIBFT_DIR)/libft.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean


fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all
