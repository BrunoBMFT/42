/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:48 by brfernan          #+#    #+#             */
/*   Updated: 2025/05/12 15:01:57 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

char	*remove_spaces(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			str[j++] = str[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\r' || *str == '\v' || *str == '\f')
		str++;
	return (str);
}

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
