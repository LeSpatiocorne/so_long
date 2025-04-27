/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 03:14:13 by nidruon           #+#    #+#             */
/*   Updated: 2025/04/27 02:11:32 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	flood_fill(t_game *game, int x, int y, int **visited, int ignore_exit)
{
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return;
	if (game->map.grid[y][x] == '1' || visited[y][x])
		return;
	if (ignore_exit && game->map.grid[y][x] == 'E')
		return;

	visited[y][x] = 1;

	flood_fill(game, x + 1, y, visited, ignore_exit);
	flood_fill(game, x - 1, y, visited, ignore_exit);
	flood_fill(game, x, y + 1, visited, ignore_exit);
	flood_fill(game, x, y - 1, visited, ignore_exit);
}

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

int	validate_path(t_game *game)
{
	int	**visited;
	int	y;
	int	x;

	visited = (int **)malloc(sizeof(int *) * game->map.height);
	if (!visited)
		return (so_error("Memory allocation failed"));
	
	y = 0;
	while (y < game->map.height)
	{
		visited[y] = (int *)malloc(sizeof(int) * game->map.width);
		if (!visited[y])
		{
			while (--y >= 0)
				free(visited[y]);
			free(visited);
			return (so_error("Memory allocation failed"));
		}
		x = 0;
		while (x < game->map.width)
		{
			visited[y][x] = 0;
			x++;
		}
		y++;
	}
	flood_fill(game, game->map.player_x, game->map.player_y, visited, 1);
	if (!check_accessible(game, visited, 0))
	{
		y = 0;
		while (y < game->map.height)
		{
			free(visited[y]);
			y++;
		}
		free(visited);
		return (so_error("Invalid path: collectibles not accessible without passing through exit"));
	}
	reset_visited(visited, game->map.height, game->map.width);
	flood_fill(game, game->map.player_x, game->map.player_y, visited, 0);
	if (!check_accessible(game, visited, 1))
	{
		y = 0;
		while (y < game->map.height)
		{
			free(visited[y]);
			y++;
		}
		free(visited);
		return (so_error("Invalid path: exit not accessible"));
	}

	y = 0;
	while (y < game->map.height)
	{
		free(visited[y]);
		y++;
	}
	free(visited);
	return (1);
} 