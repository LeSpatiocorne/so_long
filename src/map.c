#include "so_long.h"

static int count_map_size(t_game *game, int fd)
{
    char    *line;
    int     width;
    int     height;

    height = 0;
    width = 0;
    line = get_next_line(fd);
    if (!line)
    {
        ft_printf("Error: Empty map file\n");
        return (0);
    }
    while (line)
    {
        if (height == 0)
            width = ft_strlen(line);
        else if (width != (int)ft_strlen(line))
        {
            ft_printf("Error: Map must be rectangular. Line %d has different width\n", height + 1);
            free(line);
            return (0);
        }
        height++;
        free(line);
        line = get_next_line(fd);
    }
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

static int allocate_map(t_game *game)
{
    int i;

    game->map.grid = (char **)malloc(sizeof(char *) * game->map.height);
    if (!game->map.grid)
        return (0);
    i = 0;
    while (i < game->map.height)
    {
        game->map.grid[i] = (char *)malloc(sizeof(char) * (game->map.width + 1));
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

static int fill_map(t_game *game, int fd)
{
    char    *line;
    int     i;
    int     j;

    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        j = 0;
        while (line[j])
        {
            game->map.grid[i][j] = line[j];
            if (line[j] == 'P')
            {
                game->map.player_x = j;
                game->map.player_y = i;
            }
            else if (line[j] == 'E')
            {
                game->map.exit_x = j;
                game->map.exit_y = i;
            }
            else if (line[j] == 'C')
                game->map.collectibles++;
            j++;
        }
        game->map.grid[i][j] = '\0';
        free(line);
        i++;
        line = get_next_line(fd);
    }
    return (1);
}

int parse_map(t_game *game, char *map_path)
{
    int fd;

    ft_printf("Opening map file: %s\n", map_path);
    fd = open(map_path, O_RDONLY);
    if (fd < 0)
    {
        ft_printf("Error: Could not open map file\n");
        return (0);
    }
    
    if (!count_map_size(game, fd))
    {
        close(fd);
        return (0);
    }
    close(fd);
    
    fd = open(map_path, O_RDONLY);
    if (fd < 0)
    {
        ft_printf("Error: Could not reopen map file\n");
        return (0);
    }
    
    if (!allocate_map(game))
    {
        ft_printf("Error: Memory allocation failed\n");
        close(fd);
        return (0);
    }
    
    if (!fill_map(game, fd))
    {
        free_map(game);
        close(fd);
        return (0);
    }
    close(fd);
    ft_printf("Map parsed successfully\n");
    return (1);
}

static int check_walls(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            if (i == 0 || i == game->map.height - 1 || 
                j == 0 || j == game->map.width - 1)
            {
                if (game->map.grid[i][j] != '1')
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

static int check_elements(t_game *game)
{
    int i;
    int j;
    int player;
    int exit;

    player = 0;
    exit = 0;
    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            if (game->map.grid[i][j] == 'P')
                player++;
            else if (game->map.grid[i][j] == 'E')
                exit++;
            else if (game->map.grid[i][j] != '0' && game->map.grid[i][j] != '1' && 
                    game->map.grid[i][j] != 'C')
                return (0);
            j++;
        }
        i++;
    }
    return (player == 1 && exit == 1 && game->map.collectibles > 0);
}

int validate_map(t_game *game)
{
    if (!check_walls(game))
        return (0);
    if (!check_elements(game))
        return (0);
    return (1);
}

void free_map(t_game *game)
{
    int i;

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
} 