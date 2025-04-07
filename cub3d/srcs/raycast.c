/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:46:55 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/07 19:39:15 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	hit_inter(t_data *data, float y, float x)
{
	size_t	map_y;
	size_t	map_x;

	map_x = floor(x / SCALE);
	map_y = floor(y / SCALE);
	if (map_y < 0 || map_x < 0
		|| map_y >= data->map_height
		|| map_x >= ft_strlen(data->map[map_y]))
		return (false);
	if (data->map[map_y][map_x] == '1'
		|| (data->map[map_y][map_x] == 'D'
		&& !data->door_opened))
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

int	get_color(t_data *data, t_coord coord, t_coord texture, bool vert)
{
	if (vert)
	{
		if (coord.x > data->p_x)
			return (get_pixel(&data->east, texture.x, texture.y));
		else
			return (get_pixel(&data->west, texture.x, texture.y));
	}
	if (coord.y > data->p_y)
		return (get_pixel(&data->south, texture.x, texture.y));
	return (get_pixel(&data->north, texture.x, texture.y));
}

void	limit_check(t_data *data, int *top, int *bot)
{
	if (*top < 0)
		*top = 0;
	if (*bot > data->win_height)
		*bot = data->win_height;
}

int	get_wall_height(t_data *data, float hyp, float angle)
{
	return ((SCALE * (data->win_width / 2) / tan(rad(FOV) / 2))
		/ (hyp * cos(rad(angle - data->p_angle))));
}

int	get_text_x(t_data *data, t_coord coord, bool vert)
{
	if (vert)
		return (fmodf(coord.y, SCALE) * data->north.width / SCALE);
	return (coord.x = fmodf(coord.x, SCALE) * data->north.width / SCALE);
}

void	draw_wall_section(t_data *data, t_draw *info)
{
	int		height;
	int		top;
	int		bot;
	float	tex_pos;
	t_coord	texture;

	height = get_wall_height(data, info->hyp, info->angle);
	top = (data->win_height / 2) - (height / 2);
	bot = (data->win_height / 2) + (height / 2);
	limit_check(data, &top, &bot);
	texture.x = get_text_x(data, info->coord, info->vert);
	tex_pos = (top - data->win_height / 2 + height / 2)
		* (float)data->north.height / height;
	while (top < bot)
	{
		texture.y = tex_pos;
		if (texture.y >= data->north.height)
			texture.y = data->north.height - 1;
		put_pixel(data, top, info->section,
			get_color(data, info->coord, texture, info->vert));
		tex_pos += (float)data->north.height / height;
		top++;
	}
}

void	decide_dist(t_draw *info, bool which, float *dist, t_coord *coord)
{
	info->hyp = dist[which];
	info->coord = coord[which];
	info->vert = which;
}

void	raycast(t_data *data)
{
	int		section;
	float	angle;
	t_coord	coord[2];
	float	dist[2];
	t_draw	info;

	angle = data->p_angle - FOV / 2;
	section = 0;
	while (section < data->win_width)
	{
		dist[0] = inter_v_step(data, angle, &coord[0]);
		dist[1] = inter_h_step(data, angle, &coord[1]);
		info.angle = angle;
		info.section = section;
		if (dist[0] < dist[1])
			decide_dist(&info, 0, dist, coord);
		else
			decide_dist(&info, 1, dist, coord);
		draw_wall_section(data, &info);
		angle = angle + (FOV * 0.00078125);
		section++;
	}
}
