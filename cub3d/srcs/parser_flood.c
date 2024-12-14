/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 02:49:46 by bruno             #+#    #+#             */
/*   Updated: 2024/12/14 13:50:43 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_flood(t_data *data)
{
	int	y;
	int	x;

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
		x = 0;
		while (data->map[y][x])
			data->visited[y][x++] = false;
		y++;
	}
}

void	find_start(t_data *data, int *ystart, int *xstart)
{
	int	y;
	int	x;
	int	starts;

	y = 0;
	starts = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NESW", data->map[y][x]))
			{
				*ystart = y;
				*xstart = x;
				starts++;
			}
			x++;
		}
		y++;
	}
	if (starts != 1)
		error(data, "Invalid start position");
}

bool	flood(t_data *data, int y, int x)
{
	if (y < 0 || x < 0 || !data->map[y]
		|| x >= (int)ft_strlen(data->map[y])
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
	int	ystart;
	int	xstart;

	init_flood(data);
	find_start(data, &ystart, &xstart);
	if (!flood(data, ystart, xstart))
		error(data, "Map is invalid");
}
