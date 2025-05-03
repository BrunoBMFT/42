/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:48 by bruno             #+#    #+#             */
/*   Updated: 2025/04/23 14:03:41 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_enclosed(char **map, size_t y, size_t x)
{
	if (y == 0 || x == 0 || !map[y + 1] || !map[y - 1]
		|| x >= ft_strlen(map[y]) - 1
		|| x >= ft_strlen(map[y - 1])
		|| x >= ft_strlen(map[y + 1])
		|| !ft_strchr(POSSIBLE, map[y - 1][x])
		|| !ft_strchr(POSSIBLE, map[y + 1][x])
		|| !ft_strchr(POSSIBLE, map[y][x + 1])
		|| !ft_strchr(POSSIBLE, map[y][x - 1]))
		return (false);
	return (true);
}

bool	map_check(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	data->map_width = 0;
	while (data->map[y])
	{
		if (!is_allowed(data->map[y]))
			return (error("Invalid character in map"));
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("0NESWD", data->map[y][x]))
			{
				if (!is_enclosed(data->map, y, x))
					return (error("Map not enclosed"));
			}
			if (data->map_width < x)
				data->map_width = x;
			x++;
		}
		y++;
	}
	data->map_height = y;
	return (true);
}
