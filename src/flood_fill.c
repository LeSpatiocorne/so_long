/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 04:55:19 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/28 04:57:15 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_invalid(t_game *game, t_flood *flood, int x, int y)
{
	if (x < 0 || x >= game->map.width)
		return (1);
	if (y < 0 || y >= game->map.height)
		return (1);
	if (game->map.grid[y][x] == '1' || flood->visited[y][x])
		return (1);
	if (flood->ignore_exit && game->map.grid[y][x] == 'E')
		return (1);
	return (0);
}

void	flood_fill(t_game *game, t_flood *flood, int x, int y)
{
	if (is_invalid(game, flood, x, y))
		return ;
	flood->visited[y][x] = 1;
	flood_fill(game, flood, x + 1, y);
	flood_fill(game, flood, x - 1, y);
	flood_fill(game, flood, x, y + 1);
	flood_fill(game, flood, x, y - 1);
}
