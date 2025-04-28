NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -L./minilibx-linux -lmlx -lXext -lX11

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

SRCS =	src/count_map_size.c \
		src/error.c \
		src/flood_fill.c \
		src/game.c \
		src/map.c \
		src/parse_map.c \
		src/path_validation.c \
		src/so_long.c \
		src/utils.c \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Couleurs pour les messages
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling libft...$(NC)"
	@make -C libft
	@echo "$(GREEN)Compiling minilibx...$(NC)"
	@make -C minilibx-linux
	@echo "$(GREEN)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(GREEN)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I./libft -I./minilibx-linux -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@make clean -C libft
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Cleaning everything...$(NC)"
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
