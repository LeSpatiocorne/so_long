/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 05:11:10 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/28 18:02:10 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup_game(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->coin_img)
		mlx_destroy_image(game->mlx, game->coin_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map(game);
}

void	free_map(t_game *game)
{
	int	i;

	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			if (game->map.grid[i])
				free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
		game->map.grid = NULL;
	}
}

int	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->wall_img = NULL;
	game->floor_img = NULL;
	game->coin_img = NULL;
	game->player_img = NULL;
	game->exit_img = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.player_x = 0;
	game->map.player_y = 0;
	game->map.exit_x = 0;
	game->map.exit_y = 0;
	game->map.collectibles = 0;
	game->moves = 0;
	game->collected = 0;
	return (1);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 17, 0, close_game, game);
}
