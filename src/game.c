/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 03:14:13 by nidruon           #+#    #+#             */
/*   Updated: 2025/04/28 20:09:38 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_game(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (i++, i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor_img,
				j * TILE_SIZE, i * TILE_SIZE);
			if (game->map.grid[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall_img,
					j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.grid[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->coin_img,
					j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map.grid[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit_img,
					j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->player_img,
		game->map.player_x * TILE_SIZE, game->map.player_y * TILE_SIZE);
}

static int	can_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map.width
		|| new_y < 0 || new_y >= game->map.height)
		return (0);
	if (game->map.grid[new_y][new_x] == '1')
		return (0);
	if (game->map.grid[new_y][new_x] == 'E'
		&& game->collected != game->map.collectibles)
		return (0);
	return (1);
}

static void	move_player(t_game *game, int new_x, int new_y, int keycode)
{
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->collected++;
		game->map.grid[new_y][new_x] = '0';
	}
	else if (game->map.grid[new_y][new_x] == 'E'
		&& game->collected == game->map.collectibles)
	{
		ft_printf("You won in %d moves!\n", game->moves + 1);
		close_game(game);
	}
	game->map.grid[game->map.player_y][game->map.player_x] = '0';
	game->map.player_x = new_x;
	game->map.player_y = new_y;
	game->map.grid[new_y][new_x] = 'P';
	if (keycode == KEY_W || keycode == KEY_Z || keycode == KEY_S || 
		keycode == KEY_A || keycode == KEY_Q || keycode == KEY_D)
		game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player_x;
	new_y = game->map.player_y;
	ft_printf("Key pressed: %d\n", keycode);
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W || keycode == KEY_Z)
		new_y--;
	else if (keycode == KEY_S)
		new_y++;
	else if (keycode == KEY_A || keycode == KEY_Q)
		new_x--;
	else if (keycode == KEY_D)
		new_x++;
	if (can_move(game, new_x, new_y))
	{
		move_player(game, new_x, new_y, keycode);
		render_game(game);
	}
	else
		ft_printf("Cannot move to position (%d, %d)\n", new_x, new_y);
	return (0);
}

int	close_game(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
