/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 03:19:30 by nidruon           #+#    #+#             */
/*   Updated: 2025/04/28 18:25:30 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	setup_game(t_game *game, char *map_path)
{
	if (!init_game(game))
		return (0);
	if (!parse_map(game, map_path))
	{
		free_map(game);
		return (0);
	}
	if (!validate_map(game))
	{
		free_map(game);
		return (0);
	}
	if (!validate_path(game))
	{
		free_map(game);
		return (0);
	}
	if (!init_game_resources(game))
		return (0);
	render_game(game);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (so_error("Usage: ./so_long <map.ber>"));
	ft_printf("Starting game with map: %s\n", argv[1]);
	if (!setup_game(&game, argv[1]))
		return (1);
	setup_hooks(&game);
	ft_printf("Entering MLX loop...\n");
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
