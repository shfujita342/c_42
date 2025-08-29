# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/29 14:52:57 by shfujita          #+#    #+#              #
#    Updated: 2025/08/29 15:17:47 by shfujita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := so_long
CC      := cc
CFLAGS  := -Wall -Wextra -Werror

SRC = free.c \
      init.c \
      render.c \
      hooks.c \
      main.c \
      map_load.c \
      map_validate.c \
      path_check.c \
      utils.c \
      utils2.c

OBJ     := $(SRC:.c=.o)
DEPS    := so_long.h

MLX_DIR := ./minilibx-linux
MLX_INC := -I$(MLX_DIR)
MLX_LIB := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_LIB_TARGET := $(MLX_DIR)/libmlx.a

.PHONY: all clean fclean re mlx libft

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB_TARGET) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) -o $(NAME)

mlx: $(MLX_LIB_TARGET)
$(MLX_LIB_TARGET):
	@$(MAKE) -C $(MLX_DIR)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(MLX_INC)  -c $< -o $@

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(MLX_DIR) clean || true

fclean: clean
	rm -f $(NAME)

re: fclean all
