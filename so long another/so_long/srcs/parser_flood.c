/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:22:13 by bruno             #+#    #+#             */
/*   Updated: 2024/04/25 19:40:52 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

bool	set_visited(t_map *map)
{
	int	col;
	int	row;

	col = 0;
	while (map->map[col])
	{
		row = 0;
		while (map->map[col][row])
		{
			if (!is_in_array(VALID, map->map[col][row]))
				return (ft_putendl(INV_CHAR), false);
			map->visited[col][row] = false;
			row++;
		}
		col++;
	}
	map->numplayer = 0;
	map->numexit = 0;
	map->numcollectible = 0;
	return (true);
}

bool	initiate_flood(t_map *map)
{
	int	col;
	int	row;

	col = 0;
	while (map->map[col])
		col++;
	map->height = col;
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
	map->width = row;
	set_visited(map);
	return (true);
}

bool	flood_fill(t_map *map, int col, int row)
{
	if (map->map[col][row] == '1' || map->visited[col][row])
		return (false);
	map->visited[col][row] = true;
	if (col < 0 || row < 0 || !map->map[col]
		|| col >= map->height)
		return (false);
	if (map->map[col][row] == 'E')
		map->numexit++;
	if (map->map[col][row] == 'C')
		map->numcollectible++;
	if (map->map[col][row] == 'P')
		map->numplayer++;
	flood_fill(map, col, row + 1);
	flood_fill(map, col - 1, row);
	flood_fill(map, col, row - 1);
	flood_fill(map, col + 1, row);
	return (true);
}

void	find_player(t_map *map)
{
	int	col;
	int	row;

	col = 0;
	while (map->map[col])
	{
		row = 0;
		while (map->map[col][row])
		{
			if (map->map[col][row] == 'P')
			{
				map->playerpos_x = row;
				map->playerpos_y = col;
			}
			row++;
		}
		col++;
	}
}

bool	check_surroundings(t_map *map)
{
	int	col;
	int	row;

	find_player(map);
	if (!flood_fill(map, map->playerpos_y, map->playerpos_x))
		return (ft_putendl(ERR_MAP), false);
	col = 0;
	while (map->map[col])
	{
		row = 0;
		while (map->map[col][row])
		{
			if (map->map[0][row] == '0' || map->map[map->height - 1][row] == '0'
			|| map->map[col][0] == '0' || map->map[col][map->width - 1] == '0')
				return (ft_putendl(INV_WALL_BORDER), clean_map(map), false);
			row++;
		}
		if (row != map->width)
			return (ft_putendl(INV_WALL_SIZE), clean_map(map), false);
		col++;
	}
	if (col != map->height)
		return (ft_putendl(INV_WALL_SIZE), clean_map(map), false);
	map->col = col;
	map->row = row;
	if (map->numplayer == 1 && map->numcollectible == 1 && map->numexit == 1)// make multiple collectible
		return (true);
	return (ft_putendl(INV_PLAYEREXITCOLL), false);
}

bool	validate_map(t_map *map)
{
	if (!initiate_flood(map))
		return (clean_map(map), false);
	if (!check_surroundings(map))
		return (false);
	return (true);
}
