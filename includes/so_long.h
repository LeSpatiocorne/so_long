/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:47:13 by nidruon           #+#    #+#             */
/*   Updated: 2025/04/28 20:12:46 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define TILE_SIZE 32
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Z 122
# define KEY_Q 113

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	int		moves;
	int		collected;
	int		screen_width;
	int		screen_height;
	void	*wall_img;
	void	*floor_img;
	void	*coin_img;
	void	*player_img;
	void	*exit_img;
}	t_game;

typedef struct s_flood
{
	int	**visited;
	int	ignore_exit;
}	t_flood;

int		parse_map(t_game *game, char *map_path);
int		validate_map(t_game *game);
int		validate_path(t_game *game);
void	free_map(t_game *game);
void	cleanup_game(t_game *game);
int		count_map_size(t_game *game, int fd);
int		init_game(t_game *game);
int		init_mlx(t_game *game);
void	setup_hooks(t_game *game);
void	render_game(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		close_game(t_game *game);
int		so_error(char *message);
void	error_exit(char *message, t_game *game);
void	flood_fill(t_game *game, t_flood *flood, int x, int y);
int		allocate_map(t_game *game);
int		fill_map(t_game *game, int fd);
int		init_game_resources(t_game *game);
int		check_ber(char *map_name);

#endif