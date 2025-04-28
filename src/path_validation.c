/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 03:14:13 by nidruon           #+#    #+#             */
/*   Updated: 2025/04/28 05:00:27 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	check_accessible(t_game *game, int **visited, int check_exit)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (check_exit && game->map.grid[y][x] == 'E' && !visited[y][x])
				return (0);
			if (!check_exit && game->map.grid[y][x] == 'C' && !visited[y][x])
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static void	reset_visited(int **visited, int height, int width)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			visited[y][x] = 0;
			x++;
		}
		y++;
	}
}

static int	**init_visited(t_game *game)
{
	int	**visited;
	int	y;
	int	x;

	visited = (int **)malloc(sizeof(int *) * game->map.height);
	if (!visited)
		return (NULL);
	y = 0;
	while (y < game->map.height)
	{
		visited[y] = (int *)malloc(sizeof(int) * game->map.width);
		if (!visited[y])
			return (NULL);
		x = 0;
		while (x < game->map.width)
			visited[y][x++] = 0;
		y++;
	}
	return (visited);
}

static void	free_visited(int **visited, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		free(visited[y]);
		y++;
	}
	free(visited);
}

int	validate_path(t_game *game)
{
	t_flood	flood;

	flood.visited = init_visited(game);
	if (!flood.visited)
		return (so_error("Memory allocation failed"));
	flood.ignore_exit = 1;
	flood_fill(game, &flood, game->map.player_x, game->map.player_y);
	if (!check_accessible(game, flood.visited, 0))
		return (free_visited(flood.visited, game->map.height),
			so_error("Invalid path: collectibles blocked"));
	reset_visited(flood.visited, game->map.height, game->map.width);
	flood.ignore_exit = 0;
	flood_fill(game, &flood, game->map.player_x, game->map.player_y);
	if (!check_accessible(game, flood.visited, 1))
		return (free_visited(flood.visited, game->map.height),
			so_error("Invalid path: exit not accessible"));
	free_visited(flood.visited, game->map.height);
	return (1);
}
