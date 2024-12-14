/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 02:49:46 by bruno             #+#    #+#             */
/*   Updated: 2024/12/14 02:46:05 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_flood(t_data *data)
{
	int	y;
	int	x;

	data->parser->starts = 0;
	y = 0;
	while (data->map[y])
		y++;
	data->parser->visited = ft_calloc(sizeof(bool *), y + 1);
	if (!data->parser->visited)
		error(data, "Malloc flood y fail");
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
			x++;
		data->parser->visited[y] = ft_calloc(sizeof(bool), x + 1);
		if (!data->parser->visited[y])
			error(data, "Malloc flood x fail");
		x = 0;
		while (data->map[y][x])
			data->parser->visited[y][x++] = false;
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
			if (ft_strchr("NESW", data->map[y][x]))
			{
				data->parser->y_start = y;
				data->parser->x_start = x;
				data->parser->starts++;
			}
			x++;
		}
		y++;
	}
	if (data->parser->starts != 1)
		error(data, "Invalid start position");
}

bool	flood(t_data *data, int y, int x)
{
	if (y < 0 || x < 0 || !data->map[y]
		|| x >= (int)ft_strlen(data->map[y])
		|| data->map[y][x] == ' ')
		return (false);
	if (data->parser->visited[y][x] || data->map[y][x] == '1')
		return (true);
	data->parser->visited[y][x] = true;
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
	init_flood(data);
	find_start(data);
	if (!flood(data, data->parser->y_start, data->parser->x_start))
		error(data, "Map is invalid");
}
