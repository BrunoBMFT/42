/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/04/05 01:44:51 by brfernan         ###   ########.fr       */
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

void	loop_player2(t_data *data, float y, float x, int color)
{
	int	i = 0;
	while (i < SCALE / 4)
	{
		int j = 0;
		while (j < SCALE / 4)
		{
			put_pixel(data, y + i - 2, x + j - 2, color);
			j++;
		}
		i++;
	}
}

void	check_steps(float angle, float *y_step, float *x_step)
{
	int	y_dir;
	int	x_dir;
	if ((angle > 315 && angle <= 360) || (angle >= 0 && angle <= 135)){
		y_dir = -1;
		x_dir = 1;
	}
	else if ((angle > 135 && angle <= 315)){
		y_dir = 1;
		x_dir = -1;
	}
	if ((angle >= 0 && angle <= 45) || (angle > 135 && angle <= 225)
	|| (angle > 315 && angle <= 360)){
		*x_step = x_dir * tan(rad(angle));
		*y_step = y_dir;
	}
	else if ((angle > 45 && angle <= 135) || (angle > 225 && angle <= 315)){
		*y_step = y_dir / tan(rad(angle));
		*x_step = x_dir;
	}
}

// float	find_distance(t_data *data, float angle)
// {
// 	float	y_step;
// 	float	x_step;
// 	angle_correct(&angle);	
// 	check_steps(angle, &y_step, &x_step);
// 	float y = data->p_y * SCALE, x = data->p_x * SCALE;
// 	int map_y = floor (y / SCALE);
// 	int map_x = floor (x / SCALE);
// 	// put_pixel(data, y, x, GREEN);
// 	//check for y = 0, x = 0, outside map
// 	while (data->map[map_y] && data->map[map_y][map_x] && data->map[map_y][map_x] != '1')
// 	{
// 		map_y = floor(y / SCALE);
// 		map_x = floor(x / SCALE);
// 		y += y_step;
// 		x += x_step;
// 		if (y < 0 || x < 0 || y > data->win_height || x > data->win_width)//needed?
// 			break ;
// 		put_pixel(data, y, x, GREEN);
// 	}
// 	float dif_y = data->p_y - y, dif_x = data->p_x * SCALE - x;
// 	return (sqrt(pow(dif_y, 2) + pow(dif_x, 2)));
// }

//angles are wrong
float	inter_h_step(t_data *data, float angle)
{
	angle_correct(&angle);
	int y_dir, x_dir;
	if (fabs(tan(rad(angle))) < 0.0001)//wtf
		return (INFINITY);
	if ((angle > 315 && angle <= 360) || (angle >= 0 && angle <= 135)){
		y_dir = -1;
		x_dir = 1;
	}
	else if ((angle > 135 && angle <= 315)){
		y_dir = 1;
		x_dir = -1;
	}
	
	float x_step = SCALE * x_dir;
	float y_step = x_step / tan(rad(angle));

	// ! WHY THE FUCK DOES YSTEP GO NEGATIVE AND NOT ACCEPTED ANYWHERE
	printf("y %.2f x %2.f\n", y_step, x_step);
	
	float x = floor(data->p_x / SCALE) * SCALE;//can be set outside
	float y = data->p_y + (x - data->p_x) / tan(rad(angle));
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
	float	y_step;
	float	x_step;
	angle_correct(&angle);
	int y_dir, x_dir;
	if ((angle > 315 && angle <= 360) || (angle >= 0 && angle <= 135)){
		y_dir = -1;
		x_dir = 1;
	}
	else if ((angle > 135 && angle <= 315)){
		y_dir = 1;
		x_dir = -1;
	}
	
	y_step = SCALE * y_dir;
	x_step = y_step * tan(rad(angle));
	
	float y = floor(data->p_y / SCALE) * SCALE;
	if (y_dir == 1)
		y += SCALE;
	else
		y -= 0.0001;
	float x = data->p_x + (y - data->p_y) * tan(rad(angle));//check angle 90
	
	//big problem char 24,31
	while (1)
	{
		int map_y = floor(y / SCALE);
		int map_x = floor(x / SCALE);
		// put_pixel(data, y, x, GREEN);
		if (map_y < 0 || map_x < 0 || map_y >= data->win_height || map_x >= ft_strlen(data->map[map_y]))//needed?
			break ;
		if (data->map[map_y][map_x] == '1')
			break ;
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
	// put_pixel(data, data->p_y, data->p_x, GREEN);
	int i = 0;
	float angle = data->p_angle - 32;//related to facing angle
	// printf("height %d width %d\n", data->map_height, data->map_width);
	while (i < data->win_width)
	{
		// float hyp = find_distance(data, angle);
		// draw_wall_section(data, hyp, i);
		//do inters
		// float v = inter_v_step(data, angle);
			float h = inter_h_step(data, angle);
		// if (v < h)
			// draw_wall_section(data, v, i);
		// else
			// draw_wall_section(data, h, i);
		
		
		
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
