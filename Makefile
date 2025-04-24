NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Detect OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    MLX_FLAGS = -Lminilibx/linux -lmlx -lXext -lX11
    MLX_INC = -Iminilibx/linux
else
    MLX_FLAGS = -Lminilibx/opengl -lmlx -framework OpenGL -framework AppKit
    MLX_INC = -Iminilibx/opengl
endif

LIBFT = -Llibft -lft

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: libft mlx $(NAME)

libft:
	make -C libft

mlx:
ifeq ($(UNAME_S),Linux)
	make -C minilibx/linux
else
	make -C minilibx/opengl
endif

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -Ilibft $(MLX_INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean
ifeq ($(UNAME_S),Linux)
	make -C minilibx/linux clean
else
	make -C minilibx/opengl clean
endif

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft mlx
