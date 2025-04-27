#include "so_long.h"

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (so_error("MLX initialization failed"));
	
	// Définir des dimensions d'écran par défaut
	game->screen_width = 1920;
	game->screen_height = 1080;
	
	ft_printf("MLX initialized successfully\n");
	return (1);
}

static int	create_window(t_game *game)
{
	int	window_width;
	int	window_height;

	window_width = game->map.width * TILE_SIZE;
	window_height = game->map.height * TILE_SIZE;
	
	ft_printf("Calculated window size: %dx%d\n", window_width, window_height);
	
	if (window_width > game->screen_width)
	{
		ft_printf("Window width (%d) exceeds screen width (%d), adjusting...\n", 
			window_width, game->screen_width);
		window_width = game->screen_width;
	}
	if (window_height > game->screen_height)
	{
		ft_printf("Window height (%d) exceeds screen height (%d), adjusting...\n", 
			window_height, game->screen_height);
		window_height = game->screen_height;
	}
	
	ft_printf("Creating window with dimensions: %dx%d\n", window_width, window_height);
	
	game->win = mlx_new_window(game->mlx, window_width, window_height, "so_long");
	if (!game->win)
		return (so_error("Window creation failed"));
	ft_printf("Window created successfully\n");
	return (1);
}

static int	load_images(t_game *game)
{
	int	img_width;
	int	img_height;

	img_width = TILE_SIZE;
	img_height = TILE_SIZE;
	ft_printf("Loading images...\n");
	
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "assets/brickwall.xpm", &img_width, &img_height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "assets/background.xpm", &img_width, &img_height);
	game->coin_img = mlx_xpm_file_to_image(game->mlx, "assets/coin.xpm", &img_width, &img_height);
	game->player_img = mlx_xpm_file_to_image(game->mlx, "assets/player.xpm", &img_width, &img_height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "assets/exit.xpm", &img_width, &img_height);

	if (!game->wall_img || !game->floor_img || !game->coin_img || 
		!game->player_img || !game->exit_img)
	{
		ft_printf("Failed to load images:\n");
		if (!game->wall_img) ft_printf("- wall.xpm\n");
		if (!game->floor_img) ft_printf("- background.xpm\n");
		if (!game->coin_img) ft_printf("- coin.xpm\n");
		if (!game->player_img) ft_printf("- player.xpm\n");
		if (!game->exit_img) ft_printf("- exit.xpm\n");
		return (so_error("Failed to load images"));
	}
	ft_printf("All images loaded successfully\n");
	return (1);
}

int	init_game(t_game *game)
{
	ft_printf("Initializing game...\n");
	ft_bzero(game, sizeof(t_game));
	if (!init_mlx(game))
		return (0);
	game->moves = 0;
	game->collected = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (so_error("Usage: ./so_long <map.ber>"));
	
	ft_printf("Starting game with map: %s\n", argv[1]);
	
	if (!init_game(&game))
		return (1);
	
	if (!parse_map(&game, argv[1]))
		return (1);
	
	ft_printf("Map parsed successfully. Dimensions: %dx%d\n", game.map.width, game.map.height);
	
	if (!validate_map(&game))
		return (1);
	
	ft_printf("Map validated successfully\n");

	if (!create_window(&game))
		return (1);
	if (!load_images(&game))
		return (1);
	render_game(&game);
	
	ft_printf("Game rendered. Setting up hooks...\n");
	mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	
	ft_printf("Entering MLX loop...\n");
	mlx_loop(game.mlx);
	
	return (0);
} 