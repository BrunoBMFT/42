/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:02:49 by bruno             #+#    #+#             */
/*   Updated: 2025/04/03 18:28:16 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//have a putpixel for frame and one for other images?
void	put_pixel(t_data *data, int y, int x, int color)
{
	char	*offset;

	if (y < 0 || x < 0 || y > data->win_height || x > data->win_width)//check if its correct
	{
		printf("%d %d\n", y, x);
		printf("putpixel outofbounds\n");
		return ;
	}
	offset = data->frame.addr + (y * data->frame.line_len + x * (data->frame.bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}

//find better way for pixels, maybe make the scale onto put_pixel itself?
void	loop_map(t_data *data, int y, int x, int color)
{
	int	i = 0;
	while (i < SCALE)
	{
		int j = 0;
		while (j < SCALE)
		{
			put_pixel(data, (y * SCALE) + i, (x * SCALE) + j, color);
			j++;
		}
		i++;
	}
}

void	loop_player(t_data *data, int color)
{
	int	i = 0;
	while (i < SCALE / 4)
	{
		int j = 0;
		while (j < SCALE / 4)
		{
			put_pixel(data, (data->p_y * SCALE) + i - 2, (data->p_x * SCALE) + j - 2, color);
			j++;
		}
		i++;
	}
}

void	create_map(t_data *data)
{
	int	y = 0;
	while (data->map[y])
	{
		int x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				loop_map(data, y, x, WHITE);
			else if (data->map[y][x] == '0' || ft_strchr("NESW", data->map[y][x]))
				loop_map(data, y, x, GREY);
			x++;
		}
		y++;
	}
	loop_player(data, GREEN);
}

void	create_background(t_data *data)//handle the colors here
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
				put_pixel(data, y, x, FLOOR);
			else
				put_pixel(data, y, x, CEILING);
			x++;
		}
		y++;
	}
}

void	clear_img(t_data *data)//bad lol
{
	create_background(data);
}

float	rad(float deg)
{
	return (deg * PI / 180);
}


void	walk_check(t_data *data, int keysym)
{
	float step = 0.25;
	float y_temp, x_temp;
	if (keysym == 'w'){
		y_temp = data->p_y - (step * cos(rad(data->p_angle)));
		x_temp = data->p_x + (step * sin(rad(data->p_angle)));
	}
	if (keysym == 's'){
		y_temp = data->p_y + (step * cos(rad(data->p_angle)));
		x_temp = data->p_x - (step * sin(rad(data->p_angle)));
	}
	if (keysym == 'a'){
		y_temp = data->p_y - (step * sin(rad(data->p_angle)));
		x_temp = data->p_x - (step * cos(rad(data->p_angle)));
	}
	if (keysym == 'd'){
		y_temp = data->p_y + (step * sin(rad(data->p_angle)));
		x_temp = data->p_x + (step * cos(rad(data->p_angle)));
	}
	int map_y = floor (y_temp), map_x = floor (x_temp);
	if (data->map[map_y] && data->map[map_y][map_x] && data->map[map_y][map_x] != '1'){
		data->p_y = y_temp;
		data->p_x = x_temp;
	}
}

int	input(int keysym, t_data *data)
{
	if (keysym == XK_Escape){	
		clean_everything(data);
		exit(0);
	}
	if (ft_strchr("wasd", keysym) || keysym == XK_Left || keysym == XK_Right)
	{
		if (keysym == XK_Right)
			data->p_angle += 10;
		if (keysym == XK_Left)
			data->p_angle -= 10;
		if (ft_strchr("wasd", keysym))
			walk_check(data, keysym);
		create_frame(data);
	}
	return (0);
}
