/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:15:00 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/28 18:18:20 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	fill_map_cell(t_game *game, char c, int i, int j)
{
	game->map.grid[i][j] = c;
	if (c == 'P')
	{
		game->map.player_x = j;
		game->map.player_y = i;
	}
	else if (c == 'E')
	{
		game->map.exit_x = j;
		game->map.exit_y = i;
	}
	else if (c == 'C')
		game->map.collectibles++;
}

int	fill_map(t_game *game, int fd)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		j = 0;
		while (line[j] && line[j] != '\n')
		{
			fill_map_cell(game, line[j], i, j);
			j++;
		}
		game->map.grid[i][j] = '\0';
		free(line);
		i++;
		line = get_next_line(fd);
	}
	cleanup_gnl_buffer(fd);
	return (1);
}

int	allocate_map(t_game *game)
{
	int	i;

	game->map.grid = (char **)malloc(sizeof(char *) * game->map.height);
	if (!game->map.grid)
		return (0);
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = (char *)malloc(sizeof(char)
				* (game->map.width + 1));
		if (!game->map.grid[i])
		{
			while (--i >= 0)
				free(game->map.grid[i]);
			free(game->map.grid);
			game->map.grid = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}
