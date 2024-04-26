/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:24:20 by bruno             #+#    #+#             */
/*   Updated: 2024/04/26 01:52:17 by bruno            ###   ########.fr       */
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

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (!is_in_array(VALID, map->map[y][x]))
				return (ft_putendl(INV_CHAR), false);
			if (map->map[y][x] == 'P')
			{
				map->playerpos_x = x;
				map->playerpos_y = y;
			}
			x++;
		}
		map->width = x;
		y++;
	}
	map->height = y;
	return (true);
}
