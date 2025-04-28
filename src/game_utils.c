/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:30:00 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/28 18:26:41 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (so_error("MLX initialization failed"));
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
	if (window_width > game->screen_width)
		window_width = game->screen_width;
	if (window_height > game->screen_height)
		window_height = game->screen_height;
	game->win = mlx_new_window(game->mlx,
			window_width, window_height, "so_long");
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
	game->wall_img = mlx_xpm_file_to_image(game->mlx,
			"assets/brickwall.xpm", &img_width, &img_height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx,
			"assets/background.xpm", &img_width, &img_height);
	game->coin_img = mlx_xpm_file_to_image(game->mlx,
			"assets/coin.xpm", &img_width, &img_height);
	game->player_img = mlx_xpm_file_to_image(game->mlx,
			"assets/player.xpm", &img_width, &img_height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx,
			"assets/exit.xpm", &img_width, &img_height);
	if (!game->wall_img || !game->floor_img || !game->coin_img
		|| !game->player_img || !game->exit_img)
		return (so_error("Failed to load images"));
	ft_printf("All images loaded successfully\n");
	return (1);
}

int	init_game_resources(t_game *game)
{
	if (!init_mlx(game))
	{
		free_map(game);
		return (0);
	}
	if (!create_window(game))
	{
		free_map(game);
		return (0);
	}
	if (!load_images(game))
	{
		free_map(game);
		return (0);
	}
	return (1);
}
