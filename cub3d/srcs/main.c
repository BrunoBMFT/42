/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/04/06 05:29:51 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	angle_correct(float *angle)
{
	while (*angle < 0)
		*angle += 360;
	while (*angle >= 360)
		*angle -= 360;
}

float	inter_h_step(t_data *data, float angle)
{
	angle_correct(&angle);
	// if (fabs(tan(rad(angle))) < 0.0001)//wtf
	// 	return (INFINITY);
	int y_dir, x_dir;
	if (angle >= 0 && angle <= 180){
		y_dir = -1;
		x_dir = 1;
	} else {
		y_dir = 1;
		x_dir = -1;
	}
	
	float x_step = SCALE * x_dir;
	float y_step = SCALE / tan(rad(angle)) * y_dir;
	
	float x = floor(data->p_x / SCALE) * SCALE;//can be set outside
	float y = data->p_y + (x - data->p_x) / tan(rad(angle)) * x_dir;
	//big problem char 24,31
	put_pixel(data, y, x, GREEN);
	while (1)
	{
		int map_y = floor(y / SCALE);
		int map_x = floor(x / SCALE);
		if (map_y < 0 || map_x < 0 || map_y >= data->map_height || map_x >= ft_strlen(data->map[map_y]))//needed?
			break ;
		if (data->map[map_y][map_x] == '1')
			break ;
		put_pixel(data, y, x, GREEN);
		y += y_step;
		x += x_step;
	}
	float dif_y = data->p_y - y, dif_x = data->p_x - x;
	return (sqrt(pow(dif_y, 2) + pow(dif_x, 2)));
}

float	inter_v_step(t_data *data, float angle)
{
	angle_correct(&angle);
	int y_dir, x_dir;
	if (angle >= 90 && angle <= 270)
	{
		y_dir = 1;
		x_dir = -1;
	} else {
		y_dir = -1;
		x_dir = 1;
	}
	
	float y_step = SCALE * y_dir;
	float x_step = SCALE * tan(rad(angle)) * x_dir;
	
	float y = floor(data->p_y / SCALE) * SCALE;
	float x = data->p_x + (y - data->p_y) * tan(rad(angle)) * y_dir;//check angle 90
	
	//big problem char 24,31
	put_pixel(data, y, x, GREEN);
	while (1)
	{
		int map_y = floor(y / SCALE);
		int map_x = floor(x / SCALE);
		if (map_y < 0 || map_x < 0 || map_y >= data->win_height || map_x >= ft_strlen(data->map[map_y]))//needed?
			break ;
		if (data->map[map_y][map_x] == '1')
			break ;
		put_pixel(data, y, x, GREEN);
		y += y_step;
		x += x_step;
	}
	float dif_y = data->p_y - y, dif_x = data->p_x - x;
	return (sqrt(pow(dif_y, 2) + pow(dif_x, 2)));
}

//missing the fisheye fix
void	draw_wall_section(t_data *data, float hyp, int i)
{
	float dist_to_plane = (data->win_width / 2) / tan(rad(64) / 2);
	int height = SCALE * dist_to_plane / hyp;

	int top = (data->win_height / 2) - (height / 2);
	int bot = (data->win_height / 2) + (height / 2);
	
	if (top < 0) top = 0;
	if (bot > data->win_height) bot = data->win_height;
	int y = top;
	while (y < bot)
	{
		int x = 0;
		while (x < 20)
		{
			put_pixel(data, y, i + x, RED);
			x++;
		}
		y++;
	}

}

void	raycast(t_data *data)
{
	data->p_y += 0.21;
	data->p_x += 0.67;
	// int angle = 0;
	// while (angle < 360)
	// {
	// 	inter_h_step(data, angle);
	// 	angle++;
	// }
	put_pixel(data, data->p_y, data->p_x, RED);
	int i = 0;
	float angle = data->p_angle - 32;//related to facing angle
	while (i < data->win_width)
	{
		float v = inter_v_step(data, angle);
		float h = inter_h_step(data, angle);
		// if (v < h)
		// 	draw_wall_section(data, v, i);
		// else
		// 	draw_wall_section(data, h, i);
		i += 20;//this is the player_fov degree by degree, 20
		angle++;
	}
}

void	create_frame(t_data *data)
{
	clear_img(data);
	create_map(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
}



int	main(int ac, char **av)
{
	t_data data;

	if (!init(ac, av, &data))
		return (clean_everything(&data), 1);
	data.p_angle = 0;

	create_frame(&data);
	
	mlx_key_hook(data.win, input, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
