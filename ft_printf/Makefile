# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/17 17:07:56 by shfujita          #+#    #+#              #
#    Updated: 2025/05/19 12:52:09 by shfujita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := libftprintf.a
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -I ./libft

LIBFT_DIR   := libft
LIBFT_SRC := \
    $(LIBFT_DIR)/ft_isalpha.c \
    $(LIBFT_DIR)/ft_isdigit.c \
    $(LIBFT_DIR)/ft_isalnum.c \
    $(LIBFT_DIR)/ft_isascii.c \
    $(LIBFT_DIR)/ft_isprint.c \
    $(LIBFT_DIR)/ft_strlen.c \
    $(LIBFT_DIR)/ft_memset.c \
    $(LIBFT_DIR)/ft_bzero.c \
    $(LIBFT_DIR)/ft_memcpy.c \
    $(LIBFT_DIR)/ft_memmove.c \
    $(LIBFT_DIR)/ft_strlcpy.c \
    $(LIBFT_DIR)/ft_strlcat.c \
    $(LIBFT_DIR)/ft_toupper.c \
    $(LIBFT_DIR)/ft_tolower.c \
    $(LIBFT_DIR)/ft_strchr.c \
    $(LIBFT_DIR)/ft_strrchr.c \
    $(LIBFT_DIR)/ft_strncmp.c \
    $(LIBFT_DIR)/ft_memchr.c \
    $(LIBFT_DIR)/ft_memcmp.c \
    $(LIBFT_DIR)/ft_strnstr.c \
    $(LIBFT_DIR)/ft_atoi.c \
    $(LIBFT_DIR)/ft_calloc.c \
    $(LIBFT_DIR)/ft_strdup.c \
    $(LIBFT_DIR)/ft_substr.c \
    $(LIBFT_DIR)/ft_strjoin.c \
    $(LIBFT_DIR)/ft_strtrim.c \
    $(LIBFT_DIR)/ft_split.c \
    $(LIBFT_DIR)/ft_itoa.c \
    $(LIBFT_DIR)/ft_strmapi.c \
    $(LIBFT_DIR)/ft_striteri.c \
    $(LIBFT_DIR)/ft_putchar_fd.c \
    $(LIBFT_DIR)/ft_putstr_fd.c \
    $(LIBFT_DIR)/ft_putendl_fd.c \
    $(LIBFT_DIR)/ft_putnbr_fd.c \
    $(LIBFT_DIR)/ft_lstnew.c \
    $(LIBFT_DIR)/ft_lstadd_front.c \
    $(LIBFT_DIR)/ft_lstsize.c \
    $(LIBFT_DIR)/ft_lstlast.c \
    $(LIBFT_DIR)/ft_lstadd_back.c \
    $(LIBFT_DIR)/ft_lstdelone.c \
    $(LIBFT_DIR)/ft_lstclear.c \
    $(LIBFT_DIR)/ft_lstiter.c \
    $(LIBFT_DIR)/ft_lstmap.c

SRC         := ft_printf.c \
               put_chr.c \
               put_nbr.c \
               put_hex.c \
               $(LIBFT_SRC)

OBJ         := $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
