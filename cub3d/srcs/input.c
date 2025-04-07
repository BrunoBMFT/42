/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 23:10:36 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/07 20:06:50 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_collisions(t_data *data, float y_temp, float x_temp)
{
	int	map_y;
	int	map_x;

	map_y = floor (y_temp);
	map_x = floor (x_temp);
	if ((data->map[map_y] && data->map[map_y][map_x]) &&
		(data->map[map_y][map_x] != '1' && !(data->map[map_y][map_x] == 'D'
		&& !data->door_opened)))
	{
		data->p_y = y_temp * SCALE;
		data->p_x = x_temp * SCALE;
	}
}

void	walk_check(t_data *data, int keysym)
{
	float	y_temp;
	float	x_temp;

	if (keysym == 'w')
	{
		y_temp = data->p_y / SCALE - W_STEP * cos(rad(data->p_angle));
		x_temp = data->p_x / SCALE + W_STEP * sin(rad(data->p_angle));
	}
	if (keysym == 's')
	{
		y_temp = data->p_y / SCALE + W_STEP * cos(rad(data->p_angle));
		x_temp = data->p_x / SCALE - W_STEP * sin(rad(data->p_angle));
	}
	if (keysym == 'a')
	{
		y_temp = data->p_y / SCALE - W_STEP * sin(rad(data->p_angle));
		x_temp = data->p_x / SCALE - W_STEP * cos(rad(data->p_angle));
	}
	if (keysym == 'd')
	{
		y_temp = data->p_y / SCALE + W_STEP * sin(rad(data->p_angle));
		x_temp = data->p_x / SCALE + W_STEP * cos(rad(data->p_angle));
	}
	check_collisions(data, y_temp, x_temp);
}

int	input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		clean_everything(data);
		exit(0);
	}
	if (ft_strchr("wasdf", keysym) || keysym == XK_Left || keysym == XK_Right)
	{
		if (keysym == XK_Right)
			data->p_angle += A_STEP;
		if (keysym == XK_Left)
			data->p_angle -= A_STEP;
		if (ft_strchr("wasd", keysym))
			walk_check(data, keysym);
		if (keysym == 'f')
		{
			if (!data->door_opened)
				data->door_opened = true;
			else
				data->door_opened = false;
		}
		create_frame(data);
	}
	return (0);
}
