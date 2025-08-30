# =========================
# so_long — 完成版 Makefile
# get_next_line: 直接ビルド or サブメイクに対応（GNL_MODE）
# =========================

NAME    := so_long
CC      := cc
CFLAGS  := -Wall -Wextra -Werror

# ---- Sources (so_long本体) ----
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

DEPS    := so_long.h

# ---- MiniLibX ----
MLX_DIR := ./minilibx-linux
MLX_INC := -I$(MLX_DIR)
MLX_LIB := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_LIB_TARGET := $(MLX_DIR)/libmlx.a

# ---- libft ----
LIBFT_DIR := ./libft
LIBFT_A   := $(LIBFT_DIR)/libft.a
# 例: ヘッダが includes/ 配下なら次の行を -I$(LIBFT_DIR)/includes に変更
LIBFT_INC := -I$(LIBFT_DIR)
LIBFT_LIB := -L$(LIBFT_DIR) -lft

# ---- get_next_line ----
GNL_DIR   := ./get_next_line
GNL_INC   := -I$(GNL_DIR)
# モード: src (デフォルト) or lib
GNL_MODE ?= src

# (A) 直接ソースビルド（デフォルト）
ifeq ($(GNL_MODE),src)
  # get_next_line ディレクトリ内の .c 全部を取り込む
  GNL_SRC := $(wildcard $(GNL_DIR)/*.c)
  SRC     += $(GNL_SRC)
  GNL_LIB :=
  GNL_BUILD :=
  GNL_CLEAN := \
	@true
  GNL_FCLEAN := \
	@true
else
# (B) libgnl.a をサブメイクしてリンク（GNL_MODE=lib のとき）
  GNL_A    := $(GNL_DIR)/libgnl.a
  GNL_LIB  := -L$(GNL_DIR) -lgnl
  GNL_BUILD := gnl
  GNL_CLEAN := \
	@$(MAKE) -C $(GNL_DIR) clean || true
  GNL_FCLEAN := \
	@$(MAKE) -C $(GNL_DIR) fclean || true
endif

OBJ := $(SRC:.c=.o)

.PHONY: all clean fclean re mlx libft gnl

# ===== top-level =====
all: $(NAME)

$(NAME): libft mlx $(GNL_BUILD) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(LIBFT_LIB) $(GNL_LIB) -o $(NAME)

# ===== sub-builds =====
mlx: $(MLX_LIB_TARGET)
$(MLX_LIB_TARGET):
	@$(MAKE) -C $(MLX_DIR)

libft: $(LIBFT_A)
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) all

# GNL_MODE=lib のときだけ有効
gnl: $(GNL_A)
$(GNL_A):
	@$(MAKE) -C $(GNL_DIR) all

# ===== compile objects =====
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(MLX_INC) $(LIBFT_INC) $(GNL_INC) -c $< -o $@

# ===== clean =====
clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(MLX_DIR) clean || true
	@$(MAKE) -C $(LIBFT_DIR) clean || true
	$(GNL_CLEAN)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean || true
	$(GNL_FCLEAN)

re: fclean all

# ===== usage hints =====
# デフォルト（GNLを直接ビルド）:
#   make
#
# get_next_line 側で libgnl.a を作るMakefileがある場合:
#   make GNL_MODE=lib
#
# 例: クリーンビルド
#   make fclean && make
