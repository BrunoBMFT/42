/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:48 by bruno             #+#    #+#             */
/*   Updated: 2025/03/07 23:51:01 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	char_allowed(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr("01NESW ", str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_enclosed(char **map, int y, int x)
{
	if (y == 0 || x == 0 || !map[y + 1] || !map[y - 1] || x >= ft_strlen(map[y]) - 1)
        return (false);
    if (x >= ft_strlen(map[y - 1]) || x >= ft_strlen(map[y + 1]))
        return (false);
	if (!ft_strchr(POSSIBLE, map[y - 1][x]))
		return (false);
	if (!ft_strchr(POSSIBLE, map[y + 1][x]))
		return (false);
	if (!ft_strchr(POSSIBLE, map[y][x + 1]))
		return (false);
	if (!ft_strchr(POSSIBLE, map[y][x - 1]))
		return (false);
	return (true);
}
//1.cub breaks
bool	map_check(t_data *data)//call this in parser
{
	int	y;
	int	x;
	int	count;
	
	//checking everything is surrounded
	y = 0;
	count = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NESW", data->map[y][x]))
				count++;
			if (ft_strchr("0NESW", data->map[y][x]))
			{
				if (!is_enclosed(data->map, y, x))
					return (error("Map not enclosed"));
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (error("Invalid player"));
	return (true);
}

bool	save_map(t_data *data)//fix
{
	int	i;
	int	count;
	int	start;
	int	j;

	i = 0;
	count = 0;
	start = 0;
	while (data->file[i])
	{
		if (char_allowed(data->file[i]))
			count++;
		if (count == 1)
			start = i;
		i++;
	}
	data->map = ft_calloc(sizeof(char *), count + 2);
	if (!data->map)
		return (error("Map allocation failed"));
	i = start;
	j = 0;
	bool	is_map = false;
	while (data->file[i])
	{
		if ((data->file[i][0] || is_map) && char_allowed(data->file[i]))
		{
			is_map = true;
			data->map[j] = ft_strdup(data->file[i]);
			if (!data->map[j])
				return (error("Map strdup failed"));
			j++;
		}
		i++;
	}
	data->map[j] = NULL;
	if (!map_check(data))
		return (false);
	return (true);
}
