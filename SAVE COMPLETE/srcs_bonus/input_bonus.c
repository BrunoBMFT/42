/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 23:10:36 by brfernan          #+#    #+#             */
/*   Updated: 2025/05/12 15:01:56 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	walk_aux(t_data *data, float y_temp, float x_temp)
{
	int	map_y;
	int	map_x;

	map_y = floor (y_temp);
	map_x = floor (x_temp);
	if ((data->map[map_y] && data->map[map_y][map_x]) &&
		(data->map[map_y][map_x] != '1' &&
		!(data->map[map_y][map_x] == 'D'
		&& ft_is_even(data->door_opened))))
	{
		data->p_y = y_temp * SCALE;
		data->p_x = x_temp * SCALE;
	}
}

void	walk(t_data *data, int keysym)
{
	float	cos_value;
	float	sin_value;

	cos_value = W_STEP * cos(rad(data->p_angle));
	sin_value = W_STEP * sin(rad(data->p_angle));
	if (keysym == 'w')
		walk_aux(data, data->p_y / SCALE - cos_value,
			data->p_x / SCALE + sin_value);
	if (keysym == 's')
		walk_aux(data, data->p_y / SCALE + cos_value,
			data->p_x / SCALE - sin_value);
	if (keysym == 'a')
		walk_aux(data, data->p_y / SCALE - sin_value,
			data->p_x / SCALE - cos_value);
	if (keysym == 'd')
		walk_aux(data, data->p_y / SCALE + sin_value,
			data->p_x / SCALE + cos_value);
}

int	input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		clean_everything(data);
		exit(0);
	}
	else if (ft_strchr("wasdfm", keysym)
		|| keysym == XK_Left || keysym == XK_Right)
	{
		if (keysym == XK_Right)
			data->p_angle += A_STEP;
		else if (keysym == XK_Left)
			data->p_angle -= A_STEP;
		else if (ft_strchr("wasd", keysym))
			walk(data, keysym);
		else if (keysym == 'f')
			data->door_opened++;
		if (keysym == 'm')
			data->map_active++;
		create_frame(data);
	}
	return (0);
}
