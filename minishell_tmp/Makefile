# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/09 20:50:29 by yseto             #+#    #+#              #
#    Updated: 2025/10/02 13:44:50 by shfujita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# ソースファイルを自動取得
SRCS = $(wildcard *.c) $(wildcard lexer/*.c) $(wildcard parser/*.c) $(wildcard execute_cmd/*.c)
OBJS = $(SRCS:.c=.o)

# libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I./includes
LDFLAGS = -lreadline          # ← readline をリンク
# Linux で ncurses が必要なら -lncurses も追加可能
# LDFLAGS = -lreadline -lncurses

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
