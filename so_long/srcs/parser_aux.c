/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:24:20 by bruno             #+#    #+#             */
/*   Updated: 2024/05/16 12:18:08 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

bool	is_in_array(char *arr, char c)
{
	while (*arr)
	{
		if (c == *arr)
			return (true);
		arr++;
	}
	return (false);
}

bool	check_char(t_map *map)
{
	int		y;
	int		x;

	map->numplayer = 0;
	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (!is_in_array(VALID, map->map[y][x]))
				return (ft_putendl(INV_CHAR), false);
			if (map->map[y][x] == 'P')
			{
				map->playerpos_x = x;
				map->playerpos_y = y;
				map->numplayer++;
			}
		}
		map->width = x;
	}
	if (map->numplayer != 1)
		return (ft_putendl(INV_PLAYEREXITCOLL), false);
	map->height = y;
	return (true);
}
