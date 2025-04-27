NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L./minilibx-linux -lmlx -lXext -lX11

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@make -C minilibx-linux
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I./libft -I./minilibx-linux -c $< -o $@

clean:
	@make clean -C libft
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
