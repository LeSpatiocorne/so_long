/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 05:20:59 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/28 17:08:18 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	allocate_map(t_game *game)
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
			return (0);
		}
		i++;
	}
	return (1);
}

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

static int	fill_map(t_game *game, int fd)
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

static int	open_map(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_printf("Error: Could not open map file: %s\n", path);
	return (fd);
}

int	parse_map(t_game *game, char *map_path)
{
	int	fd;

	ft_printf("Opening map file: %s\n", map_path);
	fd = open_map(map_path);
	if (fd < 0 || !count_map_size(game, fd))
	{
		cleanup_gnl_buffer(fd);
		return (close(fd), 0);
	}
	close(fd);
	fd = open_map(map_path);
	if (fd < 0 || !allocate_map(game))
	{
		cleanup_gnl_buffer(fd);
		return (close(fd), 0);
	}
	if (!fill_map(game, fd))
	{
		free_map(game);
		cleanup_gnl_buffer(fd);
		close(fd);
		return (0);
	}
	cleanup_gnl_buffer(fd);
	close(fd);
	ft_printf("Map parsed successfully\n");
	return (1);
}
