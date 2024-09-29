#include "../includes/sudoku.h"

bool	check_line(char **line)
{
	int y = 0;
	while (line[y])
	{
		int i = 0;
		while (line[y][i])
		{
			int j = 0;
			while (line[y][j])
			{
				if (line[y][j] == line[y][i] && i != j && line[y][i] != '.')
					return (false);
				j++;
			}
			i++;
		}
		y++;
	}
	return (true);
}

bool	is_filled(t_map *map)
{
	int y = 0;
	while (map->map[y])
	{
		int x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '.')
			{
				map->start[0] = y;
				map->start[1] = x;
				return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

//solve using recursive
void	solve(t_map *map)
{
	init_grid(map);
	if (!is_filled(map))//turn this to a while
	{
//		printf("y %d, x %d\n", map->start[0], map->start[1]);
/* 		if (!check_line(map->rows))
			return ;
		if (!check_line(map->cols))
			return ;
		if (!check_line(map->small_grids))
			return ; */
	}

}