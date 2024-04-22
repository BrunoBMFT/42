/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:22:13 by bruno             #+#    #+#             */
/*   Updated: 2024/04/22 02:00:08 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	set_visited(t_map *map)
{
	int	col;
	int	row;

	col = 0;
	while (map->map[col])
	{
		row = 0;
		while (map->map[col][row])
		{
			map->visited[col][row] = false;
			row++;
		}
		col++;
	}
}

bool	initiate_flood(t_map *map)
{
	int	col;
	int	row;

	col = 0;
	while (map->map[col])
		col++;
	map->visited = ft_calloc(sizeof(bool *), col + 1);
	if (!map->visited)
		return (ft_putendl(ERR_ALLOC), false);
	col--;
	while (col >= 0)
	{
		row = 0;
		while (map->map[col][row])
			row++;
		map->visited[col] = malloc(row * sizeof(bool));
		if (!map->visited[col])
			return (ft_putendl(ERR_ALLOC), false);
		col--;
	}
	set_visited(map);
	return (true);
}

bool	flood_fill(t_map *map, int col, int row)
{
	if (col < 0 || row < 0 || !map->map[col]
		|| row >= (int)ft_strlen(map->map[col]))
		return (false);
	if (map->map[col][row] == 'E')
		map->has_exit = true;
	if (map->map[col][row] == 'C')
		map->has_collectible = true;
	if (map->map[col][row] == 'P')
		map->has_player = true;
	if (map->map[col][row] == '1' || map->visited[col][row])
		return (true);
	map->visited[col][row] = true;
	if (!flood_fill(map, col + 1, row))
		return (false);
	if (!flood_fill(map, col - 1, row))
		return (false);
	if (!flood_fill(map, col, row + 1))
		return (false);
	if (!flood_fill(map, col, row - 1))
		return (false);
	if (!map->has_exit || !map->has_collectible || !map->has_player)
		return (false);
	return (true);
}

bool	check_surroundings(t_map *map)
{
	int	col;
	int	row;

	col = 0;
	while (map->map[col])
	{
		row = 0;
		while (map->map[col][row])
		{
			if ((map->map[col][row] || is_in_array("P", map->map[col][row])
				|| is_in_array("E", map->map[col][row])
			|| is_in_array("C", map->map[col][row]))
			&& map->visited[col][row] == false)
			{
				if (!flood_fill(map, col, row))
					return (ft_putendl(ERR_MAP), clean_map(map), false);
			}
			row++;
		}
		col++;
	}
	map->col = col;
	map->row = row;
	return (true);
}

bool	validate_map(t_map *map)
{
	if (!check_char(map))
		return (free_file(map->map), false);
	if (!initiate_flood(map))
		return (clean_map(map), false);
	if (!check_surroundings(map))
		return (false);
	return (true);
}
