/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:15:33 by bruno             #+#    #+#             */
/*   Updated: 2025/02/11 13:12:08 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	make_minimap_pixel(t_data *data, int y, int x, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->pixel_size - 2)
	{
		j = 0;
		while (j < data->pixel_size - 2)
		{
			put_pixel(data->minimap, i + (y * SCALE / data->mini_scale), j + (x * SCALE / data->mini_scale), color);
			j++;
		}
		i++;
	}
}

void	wipe_minimap(t_data *data)//makes minimap a black screen
{
	int	y;
	int	x;

	y = 0;
	while (y < data->minimap->height)
	{
		x = 0;
		while (x < data->minimap->width)
		{
			put_pixel(data->minimap, y, x, 0);
			x++;
		}
		y++;
	}
}

void	make_player(t_data *data)
{
	int	y;
	int	x;
	y = 0;
	while (y < data->player->size)
	{
		x = 0;
		while (x < data->player->size)
		{
			put_pixel(data->minimap, y + (data->player->y * SCALE / data->mini_scale)
			, x + (data->player->x * SCALE / data->mini_scale), GREEN);
			x++;
		}
		y++;
	}
}

void	make_minimap(t_data *data)
{
	int	y;
	int	x;

	wipe_minimap(data);
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				make_minimap_pixel(data, y, x, BLUE);
			else if (data->map[y][x] == '0' || ft_strchr("NESW", data->map[y][x]))
				make_minimap_pixel(data, y, x, BACK);
			else
				make_minimap_pixel(data, y, x, BACK);
			x++;
		}
		y++;
	}
	make_player(data);

	make_frame(data, data->minimap, 0, 0);
}