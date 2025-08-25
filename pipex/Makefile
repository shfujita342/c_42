# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fujit <fujit@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/21 20:38:29 by shfujita          #+#    #+#              #
#    Updated: 2025/08/25 06:27:38 by fujit            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = pipex
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
INCLUDES    = -I $(LIBFT_DIR)

SRCS = \
    main.c    \
    parse.c\
	path.c\
	child_process.c\
	execute.c\
	utils.c

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
