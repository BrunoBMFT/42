/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:46:55 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/07 07:58:12 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//if (data->map[map_y][map_x] == '1'
//	|| (data->map[map_y][map_x] == 'D' && !data->door_opened))
bool	hit_inter(t_data *data, float y, float x)
{
	int	map_y;
	int	map_x;

	map_x = floor(x / SCALE);
	map_y = floor(y / SCALE);
	if (map_y < 0 || map_x < 0
		|| map_y >= data->map_height
		|| map_x >= ft_strlen(data->map[map_y]))
		return (false);
	if (data->map[map_y][map_x] == '1')
		return (false);
	return (true);
}

t_coord	inter_h_step(t_data *data, float angle)
{
	t_coord	coord;
	int		x_dir;
	float	y_step;
	float	x_step;

	angle_correct(&angle, &x_dir, true);
	coord.x = floor(data->p_x / SCALE) * SCALE;
	if (x_dir == 1)
		coord.x += SCALE;
	else
		coord.x -= 0.0001f;
	coord.y = data->p_y + (coord.x - data->p_x) / tan(rad(angle));
	x_step = SCALE * x_dir;
	y_step = x_step / tan(rad(angle));
	while (hit_inter(data, coord.y, coord.x))
	{
		coord.y += y_step;
		coord.x += x_step;
	}
	return (coord);
}

t_coord	inter_v_step(t_data *data, float angle)
{
	t_coord	coord;
	int		y_dir;
	float	y_step;
	float	x_step;

	angle_correct(&angle, &y_dir, false);
	coord.y = floor(data->p_y / SCALE) * SCALE;
	if (y_dir == 1)
		coord.y += SCALE;
	else
		coord.y -= 0.0001f;
	coord.x = data->p_x + (coord.y - data->p_y) * tan(rad(angle));
	y_step = SCALE * y_dir;
	x_step = y_step * tan(rad(angle));
	while (hit_inter(data, coord.y, coord.x))
	{
		coord.y += y_step;
		coord.x += x_step;
	}
	return (coord);
}

void	draw_wall_section(t_data *data, float hyp, float angle, int i)
{
	int	height;
	int	top;
	int	bot;

	height = (SCALE * (data->win_width / 2) / tan(rad(64) / 2))
		/ (hyp * cos(rad(angle - data->p_angle)));
	top = (data->win_height / 2) - (height / 2);
	bot = (data->win_height / 2) + (height / 2);
	if (top < 0)
		top = 0;
	if (bot > data->win_height)
		bot = data->win_height;
	while (top < bot)
	{
		put_pixel(data, top, i, RED);
		top++;
	}
}

void	raycast(t_data *data)
{
	t_coord	v;
	t_coord	h;
	int		section;
	float	angle;

	angle = data->p_angle - FOV / 2;
	section = 0;
	while (section < data->win_width)
	{
		v = inter_v_step(data, angle);
		h = inter_h_step(data, angle);
		float v_dist = sqrt(pow(data->p_y - v.y, 2) + pow(data->p_x - v.x, 2));
		float h_dist = sqrt(pow(data->p_y - h.y, 2) + pow(data->p_x - h.x, 2));
		if (v_dist < h_dist)
			draw_wall_section(data, v_dist, angle, section);
		else
			draw_wall_section(data, h_dist, angle, section);
		section++;
		angle = angle + (FOV * 0.00078125);
	}
}
