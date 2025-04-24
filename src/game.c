#include "../includes/so_long.h"

int    cleanup_game(t_game *game)
{
    int i;

    if (game->wall_img)
        mlx_destroy_image(game->mlx, game->wall_img);
    if (game->collectible_img)
        mlx_destroy_image(game->mlx, game->collectible_img);
    if (game->exit_img)
        mlx_destroy_image(game->mlx, game->exit_img);
    if (game->player_img)
        mlx_destroy_image(game->mlx, game->player_img);
    if (game->background_img)
        mlx_destroy_image(game->mlx, game->background_img);
    
    if (game->map.grid)
    {
        i = 0;
        while (i < game->map.height)
        {
            free(game->map.grid[i]);
            i++;
        }
        free(game->map.grid);
    }
    
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
# ifdef __linux__
    if (game->mlx)
        mlx_destroy_display(game->mlx);
# endif
    free(game->mlx);
    exit(0);
    return (0);
}

static void draw_tile(t_game *game, int x, int y, void *img)
{
    mlx_put_image_to_window(game->mlx, game->win, img, 
        x * TILE_SIZE, y * TILE_SIZE);
}

int render_game(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            draw_tile(game, j, i, game->background_img);
            if (game->map.grid[i][j] == '1')
                draw_tile(game, j, i, game->wall_img);
            else if (game->map.grid[i][j] == 'C')
                draw_tile(game, j, i, game->collectible_img);
            else if (game->map.grid[i][j] == 'E')
                draw_tile(game, j, i, game->exit_img);
            j++;
        }
        i++;
    }
    draw_tile(game, game->player.x, game->player.y, game->player_img);
    return (0);
}

static int  can_move(t_game *game, int new_x, int new_y)
{
    if (new_x < 0 || new_y < 0 || 
        new_x >= game->map.width || new_y >= game->map.height)
        return (0);
    if (game->map.grid[new_y][new_x] == '1')
        return (0);
    return (1);
}

static void move_player(t_game *game, int new_x, int new_y)
{
    if (game->map.grid[new_y][new_x] == 'C')
    {
        game->player.collected++;
        game->map.grid[new_y][new_x] = '0';
    }
    else if (game->map.grid[new_y][new_x] == 'E')
    {
        if (game->player.collected == game->map.collectibles)
        {
            ft_printf("You won in %d moves!\n", game->player.moves + 1);
            cleanup_game(game);
        }
    }
    game->player.x = new_x;
    game->player.y = new_y;
    game->player.moves++;
    ft_printf("Moves: %d\n", game->player.moves);
}

int handle_key(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        cleanup_game(game);
    else if (keycode == KEY_W || keycode == KEY_UP)
    {
        if (can_move(game, game->player.x, game->player.y - 1))
            move_player(game, game->player.x, game->player.y - 1);
    }
    else if (keycode == KEY_S || keycode == KEY_DOWN)
    {
        if (can_move(game, game->player.x, game->player.y + 1))
            move_player(game, game->player.x, game->player.y + 1);
    }
    else if (keycode == KEY_A || keycode == KEY_LEFT)
    {
        if (can_move(game, game->player.x - 1, game->player.y))
            move_player(game, game->player.x - 1, game->player.y);
    }
    else if (keycode == KEY_D || keycode == KEY_RIGHT)
    {
        if (can_move(game, game->player.x + 1, game->player.y))
            move_player(game, game->player.x + 1, game->player.y);
    }
    return (0);
} 