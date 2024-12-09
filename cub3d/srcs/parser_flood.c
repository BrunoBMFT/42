/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 02:49:46 by bruno             #+#    #+#             */
/*   Updated: 2024/12/09 12:30:33 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_flood(t_data *data)
{
	int	y;
	int	x;

	data->starts = 0;
	y = 0;
	while (data->map[y])
		y++;
	data->visited = ft_calloc(sizeof(bool *), y + 1);
	if (!data->visited)
		error(data, "Malloc flood y fail");
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
			x++;
		data->visited[y] = ft_calloc(sizeof(bool), x + 1);
		if (!data->visited[y])
			error(data, "Malloc flood x fail");
		y++;
	}
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			data->visited[y][x] = false;
			x++;
		}
		y++;
	}
}

void	find_start(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NEWS", data->map[y][x]))
			{
				if (data->starts == 1)
					error(data, "Too many start positions");
				data->y_start = y;
				data->x_start = x;
				data->starts++;
			}
			x++;
		}
		y++;
	}
}

bool	flood(t_data *data, int y, int x)
{
	if (y < 0 || x < 0 || !data->map[y] 
		|| x >= ft_strlen(data->map[y]) 
		|| data->map[y][x] == ' ')
		return (false);
	if (data->visited[y][x] || data->map[y][x] == '1')
		return (true);
	data->visited[y][x] = true;
	if (!flood(data, y - 1, x))
		return (false);
	if (!flood(data, y + 1, x))
		return (false);
	if (!flood(data, y, x + 1))
		return (false);
	if (!flood(data, y, x - 1))
		return (false);
	return (true);
}

void	flood_fill(t_data *data)
{
	if (!data->map || !data->map[0] || !data->map[0][0])
		error(data, "No map");
	init_flood(data);
	find_start(data);
	if (!flood(data, data->y_start, data->x_start))
		error(data, "Map is invalid");
}
