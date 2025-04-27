#include "so_long.h"

static void init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        error_exit("MLX initialization failed", game);
    
    // Set up display connection
    if (!mlx_get_screen_size(game->mlx, &game->screen_width, &game->screen_height))
        error_exit("Failed to get screen size", game);
    
    ft_printf("Screen size: %dx%d\n", game->screen_width, game->screen_height);
    ft_printf("MLX initialized successfully\n");
}

static void create_window(t_game *game)
{
    int window_width = game->map.width * TILE_SIZE;
    int window_height = game->map.height * TILE_SIZE;
    
    // Ensure window size doesn't exceed screen size
    if (window_width > game->screen_width)
        window_width = game->screen_width;
    if (window_height > game->screen_height)
        window_height = game->screen_height;
    
    ft_printf("Creating window with dimensions: %dx%d\n", window_width, window_height);
    
    game->win = mlx_new_window(game->mlx, window_width, window_height, "so_long");
    if (!game->win)
        error_exit("Window creation failed", game);
    ft_printf("Window created successfully\n");
}

static void load_images(t_game *game)
{
    int img_width = TILE_SIZE;
    int img_height = TILE_SIZE;

    ft_printf("Loading images...\n");
    game->wall_img = mlx_xpm_file_to_image(game->mlx, "assets/brickwall.xpm", &img_width, &img_height);
    game->floor_img = mlx_xpm_file_to_image(game->mlx, "assets/background.xpm", &img_width, &img_height);
    game->coin_img = mlx_xpm_file_to_image(game->mlx, "assets/coin.xpm", &img_width, &img_height);
    game->player_img = mlx_xpm_file_to_image(game->mlx, "assets/player.xpm", &img_width, &img_height);
    game->exit_img = mlx_xpm_file_to_image(game->mlx, "assets/exit.xpm", &img_width, &img_height);

    if (!game->wall_img || !game->floor_img || !game->coin_img || 
        !game->player_img || !game->exit_img)
        error_exit("Failed to load images", game);
    ft_printf("All images loaded successfully\n");
}

int init_game(t_game *game)
{
    ft_printf("Initializing game...\n");
    ft_bzero(game, sizeof(t_game));
    init_mlx(game);
    game->moves = 0;
    game->collected = 0;
    return (1);
}

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        error_exit("Usage: ./so_long <map.ber>", NULL);
    
    ft_printf("Starting game with map: %s\n", argv[1]);
    
    if (!init_game(&game))
        error_exit("Game initialization failed", &game);
    
    if (!parse_map(&game, argv[1]))
        error_exit("Map parsing failed", &game);
    
    ft_printf("Map parsed successfully. Dimensions: %dx%d\n", game.map.width, game.map.height);
    
    if (!validate_map(&game))
        error_exit("Invalid map", &game);
    
    ft_printf("Map validated successfully\n");

    create_window(&game);
    load_images(&game);
    render_game(&game);
    
    ft_printf("Game rendered. Setting up hooks...\n");
    mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);
    mlx_hook(game.win, 17, 0, close_game, &game);
    
    ft_printf("Entering MLX loop...\n");
    mlx_loop(game.mlx);
    
    return (0);
} 