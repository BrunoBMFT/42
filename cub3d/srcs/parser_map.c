/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:48 by bruno             #+#    #+#             */
/*   Updated: 2025/03/11 00:50:20 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_allowed(char *str)
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

bool	is_path(char *str)
{
	if (!ft_strncmp("NO", str, 2) || !ft_strncmp("SO", str, 2)
	|| !ft_strncmp("WE", str, 2) || !ft_strncmp("EA", str, 2)
	|| !ft_strncmp("F", str, 1) || !ft_strncmp("C", str, 1))
		return (true);
	return (false);
}

bool	save_map(t_data *data)
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
		if (!is_path(data->file[i]))
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
		if ((data->file[i][0] || is_map) && !is_path(data->file[i]))//TODO check whitespaces
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
	return (true);
}

bool	is_enclosed(char **map, int y, int x)
{
	if (y == 0 || x == 0 || !map[y + 1] || !map[y - 1]
		|| x >= ft_strlen(map[y]) - 1
		|| x >= ft_strlen(map[y - 1]) || x >= ft_strlen(map[y + 1])
		|| !ft_strchr(POSSIBLE, map[y - 1][x]) || !ft_strchr(POSSIBLE, map[y + 1][x])
		|| !ft_strchr(POSSIBLE, map[y][x + 1]) || !ft_strchr(POSSIBLE, map[y][x - 1]))
        return (false);
	return (true);
}
//WRONG CHAR
bool	map_check(t_data *data)
{
	int	y;
	int	x;
	int	count;
	
	y = 0;
	count = 0;
	while (data->map[y])
	{
		if (!is_allowed(data->map[y]))
			return (error("Invalid character in map"));
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("0NESW", data->map[y][x]))
			{
				if (!is_enclosed(data->map, y, x))
					return (error("Map not enclosed"));
			}
			if (ft_strchr("NESW", data->map[y][x]))
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		return (error("Invalid player"));
	return (true);
}
