/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:48 by bruno             #+#    #+#             */
/*   Updated: 2025/04/07 05:00:59 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_allowed(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr("01NESWD ", str[i]))
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

bool	is_empty(const char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (!(*str == ' ' || *str == '\t' || *str == '\n'
				|| *str == '\r' || *str == '\v' || *str == '\f'))
			return (false);
		str++;
	}
	return (true);
}

int	line_count(t_data *data, int *i)
{
	int	count;
	int	start;

	*i = 0;
	count = 0;
	start = 0;
	while (data->file[*i])
	{
		if (!is_path(data->file[*i]))
			count++;
		if (count == 1)
			start = *i;
		(*i)++;
	}
	*i = start;
	return (count);
}

bool	save_map(t_data *data)
{
	int		i;
	int		j;
	int		start;
	bool	is_map;

	data->map = ft_calloc(sizeof(char *), line_count(data, &i) + 2);
	if (!data->map)
		return (error("Map allocation failed"));
	j = 0;
	is_map = false;
	while (data->file[i])
	{
		if ((!is_empty(data->file[i]) || is_map)
			&& !is_path(data->file[i]))
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
	int	y;
	int	x;

	y = 0;
	data->map_width = 0;
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
			if (data->map_width < x)
				data->map_width = x;
			x++;
		}
		y++;
	}
	data->map_height = y;
	return (true);
}
