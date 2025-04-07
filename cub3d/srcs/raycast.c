/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:46:55 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/07 15:59:48 by brfernan         ###   ########.fr       */
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
	// if (data->map[map_y][map_x] == '1')

	if (data->map[map_y][map_x] == '1'
	|| (data->map[map_y][map_x] == 'D' && !data->door_opened))
		return (false);
	return (true);
}

float	inter_h_step(t_data *data, float angle, t_coord *coord)
{
	int		x_dir;
	float	y;
	float	x;
	float	y_step;
	float	x_step;

	angle_correct(&angle, &x_dir, true);
	x = floor(data->p_x / SCALE) * SCALE;
	if (x_dir == 1)
		x += SCALE;
	else
		x -= 0.0001f;
	y = data->p_y + (x - data->p_x) / tan(rad(angle));
	x_step = SCALE * x_dir;
	y_step = x_step / tan(rad(angle));
	while (hit_inter(data, y, x))
	{
		y += y_step;
		x += x_step;
	}
	coord->y = y;
	coord->x = x;
	return (sqrt(pow(data->p_y - y, 2) + pow(data->p_x - x, 2)));
}

float	inter_v_step(t_data *data, float angle, t_coord *coord)
{
	int		y_dir;
	float	y;
	float	x;
	float	y_step;
	float	x_step;

	angle_correct(&angle, &y_dir, false);
	y = floor(data->p_y / SCALE) * SCALE;
	if (y_dir == 1)
		y += SCALE;
	else
		y -= 0.0001f;
	x = data->p_x + (y - data->p_y) * tan(rad(angle));
	y_step = SCALE * y_dir;
	x_step = y_step * tan(rad(angle));
	while (hit_inter(data, y, x))
	{
		y += y_step;
		x += x_step;
	}
	coord->y = y;
	coord->x = x;
	return (sqrt(pow(data->p_y - y, 2) + pow(data->p_x - x, 2)));
}


void	draw_wall_section(t_data *data, float hyp, 
float angle, int i, t_coord coord, bool vertical_hit)
{
	int height = (SCALE * (data->win_width / 2) / tan(rad(FOV) / 2))
		/ (hyp * cos(rad(angle - data->p_angle)));
	int top = (data->win_height / 2) - (height / 2);
	int bot = (data->win_height / 2) + (height / 2);
	if (top < 0)
		top = 0;
	if (bot > data->win_height)
		bot = data->win_height;


	// while (top < bot)
	// {
	// 	put_pixel(data, top, i, RED);
	// 	top++;
	// }
	float tex_x;
	float tex_pos;
	float step;
	int tex_y;

	if (vertical_hit)
		tex_x = fmodf(coord.y, SCALE) * data->north.width / SCALE;
	else
		tex_x = fmodf(coord.x, SCALE) * data->north.width / SCALE;



	step = (float)data->north.height / height;
	tex_pos = (top - data->win_height / 2 + height / 2) * step;

	while (top < bot)
	{
		int tex_y = (int)tex_pos;
		if (tex_y >= data->north.height)
			tex_y = data->north.height - 1;

		int color;
		if (vertical_hit)
		{
			if (coord.x > data->p_x)
				color = get_pixel(&data->east, tex_x, tex_y);
			else
				color = get_pixel(&data->west, tex_x, tex_y);
		}
		else
		{
			if (coord.y > data->p_y)
				color = get_pixel(&data->south, tex_x, tex_y);
			else
				color = get_pixel(&data->north, tex_x, tex_y);
		}
		put_pixel(data, top, i, color);
		tex_pos += step;
		top++;
	}
}

void	raycast(t_data *data)
{
	float	v;
	float	h;
	int		section;
	float	angle;
	t_coord coord_v, coord_h;

	angle = data->p_angle - FOV / 2;
	section = 0;
	while (section < data->win_width)
	{
		v = inter_v_step(data, angle, &coord_v);
		h = inter_h_step(data, angle, &coord_h);
		if (v < h)
			draw_wall_section(data, v, angle, section, coord_v, false);
		else
			draw_wall_section(data, h, angle, section, coord_h, true);
		section++;
		angle = angle + (FOV * 0.00078125);// 1/128
	}
}
