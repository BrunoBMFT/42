/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:45:08 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/07 04:45:40 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	loop_map(t_data *data, int y, int x, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCALE)
	{
		j = 0;
		while (j < SCALE)
		{
			put_pixel(data, (y * SCALE) + i, (x * SCALE) + j, color);
			j++;
		}
		i++;
	}
}

void	show_dir(t_data *data)
{
	float	y;
	float	x;
	int		i;

	i = 0;
	y = data->p_y;
	x = data->p_x;
	while (i < 32)
	{
		y -= cos(rad(360 - data->p_angle)) * 0.5;
		x += sin(rad(data->p_angle)) * 0.5;
		put_pixel(data, (int)y, (int)x, RED);
		i++;
	}
}

void	loop_player(t_data *data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCALE / 2)
	{
		j = 0;
		while (j < SCALE / 2)
		{
			put_pixel(data, (data->p_y) + i - 4, (data->p_x) + j - 4, color);
			j++;
		}
		i++;
	}
	show_dir(data);
}

void	create_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				loop_map(data, y, x, WHITE);
			else if (data->map[y][x] == '0'
				|| ft_strchr("NESW", data->map[y][x]))
				loop_map(data, y, x, GREY);
			else if (data->map[y][x] == 'D')
				loop_map(data, y, x, data->color_ceiling);
			x++;
		}
		y++;
	}
	loop_player(data, GREEN);
}
