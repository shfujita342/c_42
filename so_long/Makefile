# =========================
# so_long — Makefile (Linux / minilibx-linux)
# =========================

NAME    := so_long
CC      := cc
CFLAGS  := -Wall -Wextra -Werror

# ---- Directories ----
MLX_DIR := ./minilibx-linux
LIBFT_DIR := ./libft
GNL_DIR := ./get_next_line

# ---- Includes ----
MLX_INC := -I$(MLX_DIR)
LIBFT_INC := -I$(LIBFT_DIR)         # もしヘッダが libft/includes/ にあるなら -I$(LIBFT_DIR)/includes に変更
GNL_INC := -I$(GNL_DIR)

# ---- Libraries ----
MLX_LIBS := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT_LIBS := -L$(LIBFT_DIR) -lft
MLX_A := $(MLX_DIR)/libmlx.a
LIBFT_A := $(LIBFT_DIR)/libft.a

# ---- Sources ----
SRC = \
  init.c \
  hooks.c \
  main.c \
  map_load.c \
  map_validate.c \
  path_check.c \
  render.c \
  utils.c \
  $(GNL_DIR)/get_next_line.c \
  $(GNL_DIR)/get_next_line_utils.c

OBJ := $(SRC:.c=.o)
DEPS := so_long.h

.PHONY: all clean fclean re mlx libft

# ===== top-level =====
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIBS) $(LIBFT_LIBS) -o $(NAME)

# ===== sub-builds =====
mlx: $(MLX_A)
$(MLX_A):
	@$(MAKE) -C $(MLX_DIR)

libft: $(LIBFT_A)
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) all

# ===== compile objects =====
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(MLX_INC) $(LIBFT_INC) $(GNL_INC) -c $< -o $@

# ===== clean =====
clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(MLX_DIR) clean || true
	@$(MAKE) -C $(LIBFT_DIR) clean || true

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean || true

re: fclean all
