#include "../includes/so_long.h"

void    error_exit(char *message)
{
    write(2, "Error\n", 6);
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
    exit(1);
}

int init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        error_exit("Failed to initialize MLX");
    
    // Initialize window size based on map
    game->win = mlx_new_window(game->mlx, 
        game->map.width * TILE_SIZE, 
        game->map.height * TILE_SIZE, 
        "so_long");
    if (!game->win)
        error_exit("Failed to create window");

    // Load images
    game->wall_img = mlx_xpm_file_to_image(game->mlx, "assets/brickwall.xpm", 
        &(int){TILE_SIZE}, &(int){TILE_SIZE});
    game->collectible_img = mlx_xpm_file_to_image(game->mlx, "assets/coin.xpm", 
        &(int){TILE_SIZE}, &(int){TILE_SIZE});
    game->exit_img = mlx_xpm_file_to_image(game->mlx, "assets/exit.xpm", 
        &(int){TILE_SIZE}, &(int){TILE_SIZE});
    game->player_img = mlx_xpm_file_to_image(game->mlx, "assets/player.xpm", 
        &(int){TILE_SIZE}, &(int){TILE_SIZE});
    game->background_img = mlx_xpm_file_to_image(game->mlx, "assets/background.xpm", 
        &(int){TILE_SIZE}, &(int){TILE_SIZE});

    if (!game->wall_img || !game->collectible_img || !game->exit_img || 
        !game->player_img || !game->background_img)
        error_exit("Failed to load images");

    return (1);
}

int main(int argc, char **argv)
{
    t_game  game;

    if (argc != 2)
        error_exit("Usage: ./so_long <map_file>");

    if (!load_map(&game, argv[1]))
        error_exit("Failed to load map");

    if (!validate_map(&game))
        error_exit("Invalid map");

    if (!check_path(&game))
        error_exit("No valid path in map");

    if (!init_game(&game))
        error_exit("Failed to initialize game");

    mlx_hook(game.win, 2, 1L<<0, handle_key, &game);
    mlx_hook(game.win, 17, 0, cleanup_game, &game);
    mlx_loop_hook(game.mlx, render_game, &game);
    mlx_loop(game.mlx);

    return (0);
}
