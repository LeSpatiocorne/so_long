/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_map_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 04:49:22 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/28 17:06:41 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_line_width(char *line, int width, int height)
{
	if (height == 0)
		return (ft_strlen(line));
	if (width != (int)ft_strlen(line))
	{
		ft_printf("Error: Map not rectangular at line %d\n", height + 1);
		return (-1);
	}
	return (width);
}

static int	check_map_dimensions(t_game *game, int width, int height)
{
	if (height < 3 || width < 3)
	{
		ft_printf("Error: Map must be at least 3x3\n");
		return (0);
	}
	game->map.width = width;
	game->map.height = height;
	ft_printf("Map size: %dx%d\n", width, height);
	return (1);
}

int	count_map_size(t_game *game, int fd)
{
	char	*line;
	int		width;
	int		height;

	height = 0;
	width = 0;
	line = get_next_line(fd);
	if (!line)
	{
		cleanup_gnl_buffer(fd);
		return (ft_printf("Error: Empty map file\n"), 0);
	}
	while (line)
	{
		if (ft_strchr(line, '\n'))
			*ft_strchr(line, '\n') = '\0';
		width = check_line_width(line, width, height);
		if (width == -1)
		{
			cleanup_gnl_buffer(fd);
			return (free(line), 0);
		}
		height++;
		free(line);
		line = get_next_line(fd);
	}
	return (check_map_dimensions(game, width, height));
}
