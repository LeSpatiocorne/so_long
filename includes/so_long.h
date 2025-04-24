/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidruon <nidruon@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:47:13 by nidruon           #+#    #+#             */
/*   Updated: 2025/04/24 18:23:53 by nidruon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"

# ifdef __linux__
#  include "../minilibx/linux/mlx.h"
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# else
#  include "../minilibx/opengl/mlx.h"
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# endif

# define TILE_SIZE 32

typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    int     collectibles;
    int     exit;
    int     player;
}   t_map;

typedef struct s_player
{
    int     x;
    int     y;
    int     moves;
    int     collected;
}   t_player;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    t_map   map;
    t_player player;
    void    *wall_img;
    void    *collectible_img;
    void    *exit_img;
    void    *player_img;
    void    *background_img;
}   t_game;

// Map functions
int     load_map(t_game *game, char *filename);
int     validate_map(t_game *game);
int     check_path(t_game *game);

// Game functions
int     init_game(t_game *game);
int     handle_key(int keycode, t_game *game);
int     render_game(t_game *game);
int     cleanup_game(t_game *game);

// Error handling
void    error_exit(char *message);

#endif