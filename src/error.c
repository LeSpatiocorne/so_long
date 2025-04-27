#include "so_long.h"

int	so_error(char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (0);
}

int	so_error_exit(char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	error_exit(char *message, t_game *game)
{
	if (game)
		close_game(game);
	ft_printf("Error\n%s\n", message);
	exit(1);
}
