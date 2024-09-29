#include "../includes/sudoku.h"

void	clean_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->img)
	{
		while (map->img[i])
		{
			free(map->img[i]);
		}
	}
	free(map->img);
}
