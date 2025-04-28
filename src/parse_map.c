/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 05:20:59 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/28 18:17:46 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	open_map(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_printf("Error: Could not open map file: %s\n", path);
	return (fd);
}

static int	handle_map_error(int fd, t_game *game, int free_map_needed)
{
	if (free_map_needed)
		free_map(game);
	cleanup_gnl_buffer(fd);
	close(fd);
	return (0);
}

static int	read_map_size(t_game *game, char *map_path)
{
	int	fd;

	fd = open_map(map_path);
	if (fd < 0 || !count_map_size(game, fd))
		return (handle_map_error(fd, game, 0));
	close(fd);
	return (1);
}

static int	read_map_content(t_game *game, char *map_path)
{
	int	fd;

	fd = open_map(map_path);
	if (fd < 0)
		return (handle_map_error(fd, game, 0));
	if (!allocate_map(game))
		return (handle_map_error(fd, game, 0));
	if (!fill_map(game, fd))
		return (handle_map_error(fd, game, 1));
	cleanup_gnl_buffer(fd);
	close(fd);
	return (1);
}

int	parse_map(t_game *game, char *map_path)
{
	ft_printf("Opening map file: %s\n", map_path);
	if (!read_map_size(game, map_path))
		return (0);
	if (!read_map_content(game, map_path))
		return (0);
	ft_printf("Map parsed successfully\n");
	return (1);
}
