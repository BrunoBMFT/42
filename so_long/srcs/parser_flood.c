/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:22:13 by bruno             #+#    #+#             */
/*   Updated: 2024/04/26 01:47:12 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

bool	set_visited(t_map *map)
{
	int		col;
	int		row;

	col = 0;
	while (map->map[col])
	{
		row = 0;
		if ((int)ft_strlen(map->map[col]) != map->width)
			return (ft_putendl(INV_WALL_SIZE), false);
		while (map->map[col][row])
		{
			if (map->map[0][row] != '1' || map->map[map->height - 1][row] != '1'
			|| map->map[col][0] != '1' || map->map[col][map->width - 1] != '1')
				return (ft_putendl(INV_WALL_BORDER), false);
			map->visited[col][row] = false;
			row++;
		}
		col++;
	}
	return (true);
}

bool	initiate_flood(t_map *map)
{
	int	i;

	i = 0;
	map->visited = ft_calloc(sizeof(bool *), map->height + 1);
	while (i < map->height)
	{
		map->visited[i] = ft_calloc(sizeof(bool), map->width);
		i++;
	}
	map->numcollectible = 0;
	map->numplayer = 0;
	map->numexit = 0;
	if (!set_visited(map))
		return (false);
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

bool	check_surroundings(t_map *map)
{
	if (!flood_fill(map, map->playerpos_y, map->playerpos_x))
		return (ft_putendl(ERR_MAP), false);
	if (map->numplayer != 1 || map->numcollectible != 1 || map->numexit != 1)
		return (ft_putendl(INV_PLAYEREXITCOLL), false);
	return (true);
}

bool	validate_map(t_map *map)
{
	if (!check_char(map))
		return (free_file(map->map), false);
	if (!initiate_flood(map))
		return (clean_map(map), false);
	if (!check_surroundings(map))
		return (clean_map(map), false);
	return (true);
}
