#include "../includes/sudoku.h"

void init_map(t_map *map)
{
	map->start = ft_calloc(sizeof(int), 2);
	map->cols = ft_calloc(sizeof(char *), 10);
	map->rows = ft_calloc(sizeof(char *), 10);
	map->map = ft_calloc(sizeof(char *), 10);
	map->small_grids = ft_calloc(sizeof(char *), 10);
	
	int i = 0;
	while (i <= 8)
	{
		map->cols[i] = ft_calloc(sizeof(char), 1);//maybe unneccessary
		map->rows[i] = ft_calloc(sizeof(char), 1);
		map->small_grids[i] = ft_calloc(sizeof(char), 1);
		map->map[i] = ft_calloc(sizeof(char), 1);
		i++;
	}
	map->cols[9] = NULL;
	map->rows[9] = NULL;
	map->small_grids[9] = NULL;
	map->map[9] = NULL;
}

bool	line_has_nums(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (ft_isdigitper(str[i]))
			return (true);
		i++;
	}
	return (false);
}

void	init_grid_aux(t_map *map)
{
	int	y = 0;
	while (map->map[y])
	{
		int x = 0;
		printf("%s\n", map->map[y]);
		while (map->map[y][x])
		{
			printf("y / 3 =  %d\ty %% 3 = %d\n", (y / 3), (y % 3));
			x++;
		}
		y++;
	}
}

void	init_grid(t_map *map)
{
	int y = 0;
	int	i = 0;
	while (map->img[y])
	{
		int x = 0;
		while (map->img[y][x])
		{
			if (!map->map[i])
				ft_strdup(map->img[y][x]);
			else
				ft_strjoin(map->map[i][j], map->img[y][x]);
			x++;
		}
		/* 
		int x = 0;
		int j = 0;
		while (map->img[y][x])
		{
			if (ft_isdigitper(map->img[y][x]) && map->map[i][j])
			{
				map->map[i][j] = map->img[y][x];
//				map->rows[i][j] = map->img[y][x];
//				map->cols[j][i] = map->img[y][x];
				j++;
			}
			x++;
		} */
		if (line_has_nums(map->img[y]))
			i++;
		y++;
	}
	init_grid_aux(map);
//	update_map(map);
}

void	print_map(t_map *map)
{
	int y = 0; 
	while (map->map[y])
	{
		int x = 0;
		while (map->map[y][x])
		{
			printf("%c ", map->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	update_map(t_map *map)
{
	int y = 0;
	while (map->rows[y])
	{
		int x = 0;
		while (map->rows[y][x])
		{
			map->map[y][x] = map->rows[y][x];
			x++;
		}
		y++;
	}
}
