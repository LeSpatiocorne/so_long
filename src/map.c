/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 04:41:10 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/28 05:29:16 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (i == 0 || i == game->map.height - 1
				|| j == 0 || j == game->map.width - 1)
			{
				if (game->map.grid[i][j] != '1')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_elements(t_game *game)
{
	int	i;
	int	j;
	int	player;
	int	exit;

	player = 0;
	exit = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 'P')
				player++;
			else if (game->map.grid[i][j] == 'E')
				exit++;
			else if (game->map.grid[i][j] != '0' && game->map.grid[i][j]
				!= '1' && game->map.grid[i][j] != 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (player == 1 && exit == 1 && game->map.collectibles > 0);
}

int	validate_map(t_game *game)
{
	if (!check_walls(game))
		return (0);
	if (!check_elements(game))
		return (0);
	return (1);
}
