# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shfujita <shfujita@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/01 15:39:05 by yseto             #+#    #+#              #
#    Updated: 2025/10/02 14:04:08 by shfujita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME           := libft.a
FT_PRINTF_DIR  := ft_printf
FT_FPRINTF_DIR := ft_fprintf

SRC := ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlen.c \
       ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
       ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_isalpha.c \
       ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c \
       ft_tolower.c ft_strdup.c ft_strndup.c ft_calloc.c ft_substr.c ft_strjoin.c \
       ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_strcmp.c \
       ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
       ft_strcat.c ft_strcpy.c

BONUS_SRC := ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
             ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
             ft_lstmap.c

PRINTF_SRC   := $(FT_PRINTF_DIR)/ft_printf.c $(FT_PRINTF_DIR)/ft_printf_utils.c
FPRINTF_SRC  := $(FT_FPRINTF_DIR)/ft_fprintf.c $(FT_FPRINTF_DIR)/ft_fprintf_utils.c

OBJ          := $(SRC:.c=.o)
BONUS_OBJ    := $(BONUS_SRC:.c=.o)
PRINTF_OBJ   := $(PRINTF_SRC:.c=.o)
FPRINTF_OBJ  := $(FPRINTF_SRC:.c=.o)

CC           := cc
CFLAGS       := -Wall -Wextra -Werror
AR           := ar rcs
RM           := rm -f

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(PRINTF_OBJ) $(FPRINTF_OBJ)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJ) $(BONUS_OBJ) $(PRINTF_OBJ) $(FPRINTF_OBJ)
	$(AR) $(NAME) $^

clean:
	$(RM) $(OBJ) $(BONUS_OBJ) $(PRINTF_OBJ) $(FPRINTF_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
