#include "../includes/so_long.h"

static int  count_map_size(t_game *game, int fd)
{
    char    *line;
    int     width;
    int     height;
    int     line_len;

    height = 0;
    width = 0;
    line = get_next_line(fd);
    while (line)
    {
        line_len = (int)ft_strlen(line);
        // Si la ligne se termine par \n, on le retire
        if (line[line_len - 1] == '\n')
            line_len--;
            
        if (height == 0)
            width = line_len;
        else if (width != line_len)
        {
            write(2, "Error: Inconsistent line length\n", 31);
            free(line);
            return (0);
        }
        height++;
        free(line);
        line = get_next_line(fd);
    }
    if (height == 0 || width == 0)
    {
        write(2, "Error: Map is empty\n", 19);
        return (0);
    }
    game->map.width = width;
    game->map.height = height;
    return (1);
}

static int  allocate_map(t_game *game)
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
            return (0);
        i++;
    }
    return (1);
}

static int  fill_map(t_game *game, int fd)
{
    char    *line;
    int     i;
    int     j;

    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        j = 0;
        while (j < game->map.width)
        {
            game->map.grid[i][j] = line[j];
            j++;
        }
        game->map.grid[i][j] = '\0';
        free(line);
        i++;
        line = get_next_line(fd);
    }
    return (1);
}

int load_map(t_game *game, char *filename)
{
    int fd;
    char *line;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        write(2, "Error: Cannot open file\n", 23);
        return (0);
    }
    
    // Vérifier que le fichier n'est pas vide
    line = get_next_line(fd);
    if (!line)
    {
        write(2, "Error: Empty file\n", 17);
        close(fd);
        return (0);
    }
    free(line);
    close(fd);

    // Reouvrir le fichier pour la lecture complète
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        write(2, "Error: Cannot reopen file\n", 24);
        return (0);
    }
    
    if (!count_map_size(game, fd))
    {
        write(2, "Error: Invalid map size\n", 23);
        close(fd);
        return (0);
    }
    close(fd);

    if (!allocate_map(game))
    {
        write(2, "Error: Memory allocation failed\n", 30);
        return (0);
    }

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        write(2, "Error: Cannot open file for filling\n", 35);
        return (0);
    }
    
    if (!fill_map(game, fd))
    {
        write(2, "Error: Failed to fill map\n", 25);
        close(fd);
        return (0);
    }
    close(fd);

    return (1);
}

static int  check_walls(t_game *game)
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

static int  count_elements(t_game *game)
{
    int i;
    int j;

    game->map.collectibles = 0;
    game->map.exit = 0;
    game->map.player = 0;
    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            if (game->map.grid[i][j] == 'C')
                game->map.collectibles++;
            else if (game->map.grid[i][j] == 'E')
                game->map.exit++;
            else if (game->map.grid[i][j] == 'P')
            {
                game->map.player++;
                game->player.x = j;
                game->player.y = i;
            }
            else if (game->map.grid[i][j] != '0' && game->map.grid[i][j] != '1')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int validate_map(t_game *game)
{
    if (!check_walls(game))
        return (0);
    if (!count_elements(game))
        return (0);
    if (game->map.exit != 1 || game->map.player != 1 || game->map.collectibles < 1)
        return (0);
    return (1);
}

static void flood_fill(t_game *game, int x, int y, int *collectibles, int *exit)
{
    if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
        return;
    if (game->map.grid[y][x] == '1' || game->map.grid[y][x] == 'X')
        return;
    
    if (game->map.grid[y][x] == 'C')
        (*collectibles)++;
    if (game->map.grid[y][x] == 'E')
        *exit = 1;
    
    game->map.grid[y][x] = 'X';
    
    flood_fill(game, x + 1, y, collectibles, exit);
    flood_fill(game, x - 1, y, collectibles, exit);
    flood_fill(game, x, y + 1, collectibles, exit);
    flood_fill(game, x, y - 1, collectibles, exit);
}

int check_path(t_game *game)
{
    char    **temp_grid;
    int     collectibles;
    int     exit;
    int     i;

    temp_grid = (char **)malloc(sizeof(char *) * game->map.height);
    if (!temp_grid)
        return (0);
    i = 0;
    while (i < game->map.height)
    {
        temp_grid[i] = ft_strdup(game->map.grid[i]);
        if (!temp_grid[i])
            return (0);
        i++;
    }

    // Save original grid and replace with temp
    char **original_grid = game->map.grid;
    game->map.grid = temp_grid;

    collectibles = 0;
    exit = 0;
    flood_fill(game, game->player.x, game->player.y, &collectibles, &exit);

    // Restore original grid
    game->map.grid = original_grid;

    // Free temp grid
    i = 0;
    while (i < game->map.height)
    {
        free(temp_grid[i]);
        i++;
    }
    free(temp_grid);

    return (collectibles == game->map.collectibles && exit == 1);
} 