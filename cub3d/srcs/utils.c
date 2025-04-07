/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 23:10:36 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/07 04:17:29 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// printf("%d %d\n", y, x);
// printf("putpixel out of bounds\n");
void	put_pixel(t_data *data, int y, int x, int color)
{
	char	*offset;

	if (y < 0 || x < 0 || y > data->win_height || x > data->win_width)
		return ;
	offset = data->frame.addr + (y * data->frame.line_len + x
			* (data->frame.bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}

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

void	create_background(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			if (y > data->win_height / 2)
				put_pixel(data, y, x, data->color_floor);
			else
				put_pixel(data, y, x, data->color_ceiling);
			x++;
		}
		y++;
	}
}

//bad lol
void	clear_img(t_data *data)
{
	create_background(data);
}

float	rad(float deg)
{
	return (deg * PI / 180);
}

// if ((data->map[map_y] && data->map[map_y][map_x]) && 
// 	(data->map[map_y][map_x] != '1' && !(data->map[map_y][map_x] == 'D' 
//  && !data->door_opened)))
void	check_collisions(t_data *data, float y_temp, float x_temp)
{
	int	map_y;
	int	map_x;

	map_y = floor (y_temp);
	map_x = floor (x_temp);
	if (data->map[map_y] && data->map[map_y][map_x] &&
		data->map[map_y][map_x] != '1')
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

// if (keysym == 'f'){
// 	if (!data->door_opened)
// 		data->door_opened = true;
// 	else
// 		data->door_opened = false;
// }
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
			data->p_angle += 20;
		if (keysym == XK_Left)
			data->p_angle -= 20;
		if (ft_strchr("wasd", keysym))
			walk_check(data, keysym);
		create_frame(data);
	}
	return (0);
}
