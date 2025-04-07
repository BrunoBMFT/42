/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/04/07 03:18:28 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	angle_correct(float *angle, int *dir, bool is_h)
{
	while (*angle < 0)
		*angle += 360;
	while (*angle >= 360)
		*angle -= 360;
	if (is_h)
	{
		*angle = 180 - *angle;
		if (*angle >= 0 && *angle <= 180)
			*dir = 1;
		else
			*dir = -1;
	}
	else
	{
		*angle = 360 - *angle;
		if (*angle >= 90 && *angle <= 270)
			*dir = 1;
		else
			*dir = -1;
	}
}

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

float	inter_h_step(t_data *data, float angle)
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
	return (sqrt(pow(data->p_y - y, 2) + pow(data->p_x - x, 2)));
}

float	inter_v_step(t_data *data, float angle)
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
	return (sqrt(pow(data->p_y - y, 2) + pow(data->p_x - x, 2)));
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
	float	v;
	float	h;
	int		section;
	float	angle;

	angle = data->p_angle - 32;
	section = 0;
	while (section < data->win_width)
	{
		v = inter_v_step(data, angle);
		h = inter_h_step(data, angle);
		if (v < h)
			draw_wall_section(data, v, angle, section);
		else
			draw_wall_section(data, h, angle, section);
		section++;
		angle = angle + 0.05;
	}
}

void	create_frame(t_data *data)
{
	clear_img(data);
	raycast(data);
	create_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!init(ac, av, &data))
		return (clean_everything(&data), 1);
	create_frame(&data);
	mlx_key_hook(data.win, input, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
