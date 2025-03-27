/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/03/27 20:17:59 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	rad(int deg)
{
	return (deg * PI / 180);
}


//  (screenwidth / 2 * )   hyp  / tan(rad(fov))
// ! do 3 calcs by hand with with fov 64 from center to check if it is correct 

// void	draw_wall_section(t_data *data, float hyp, int angle)//wall division
// {
// 	//section start and end need to be calculated using the angle that was sent
// 	int section_start = data->win_width / 2 + angle * 20;// *20 because of fov, each section is 20
// 	int section_end = data->win_width / 2 + angle * 20 + data->win_width / 64;
// 	int x = 0;
// 	while (x + section_start < section_end)
// 	{
// 		int line_size = data->win_height - (int)hyp;
// 		int start = 0;
// 		//have it centered
// 		// float height = hyp / tan(rad(angle));
// 		// printf("%.2f\n", height);
// 		while (start < line_size / 2)
// 		{
// 			put_pixel(&data->frame, start, x + section_start, RED);
// 			start++;
// 		}
// 		x++;
// 	}
// }

// //rename
// float	draw_single_ray(t_data *data, int d_y, int d_x, int angle)
// {
// 	d_y = d_y * SCALE;
// 	d_x = d_x * SCALE;
// 	float f_y = (float)d_y;
// 	float f_x = (float)d_x;
// 	float ori_y = f_y;
// 	float ori_x = f_x;
// 	//decide direction
// 	int y_dir;
// 	int x_dir;
// 	//dont forget loops or negatives
// 	while (angle < 0)
// 		angle += 360;
// 	while (angle >= 360)
// 		angle -= 360;
// 	if (angle >= 0 && angle <= 90)
// 	{
// 		y_dir = -1;
// 		x_dir = 1;
// 	}
// 	if (angle > 90 && angle <= 180)
// 	{
// 		y_dir = 1;
// 		x_dir = -1;
// 	}
// 	if (angle > 180 && angle <= 270)
// 	{
// 		y_dir = 1;
// 		x_dir = -1;
// 	}
// 	if (angle > 270 && angle <= 360)
// 	{
// 		y_dir = -1;
// 		x_dir = 1;
// 	}
// 	//draw ray
// 	int y = (int)round(f_y) / SCALE;
// 	int x = (int)round(f_x) / SCALE;
// 	while (data->map[y][x] != '1')
// 	{
// 		put_pixel(&data->frame, (int)f_y, (int)f_x, GREEN);
// 		y = (int)round(f_y) / SCALE;
// 		x = (int)round(f_x) / SCALE;
// 		if ((angle > 45 && angle < 135) || (angle > 225 && angle < 315))
// 		{
// 			f_x += 1 * x_dir;
// 			f_y += 1 / tan(rad(angle)) * y_dir;
// 		}
// 		else
// 		{
// 			f_y += 1 * y_dir;
// 			f_x += 1 * tan(rad(angle)) * x_dir;
// 		}
// 	}
// 	float dif_y = ori_y - f_y, dif_x = ori_x - f_x;
// 	float hyp = sqrt((dif_y * dif_y) + (dif_x * dif_x));
// 	// printf("y %.2f, x %.2f hyp %.2f\n", dif_y, dif_x, hyp);
// 	return (hyp);
// }

void	angle_dirs(int *angle, int *y_dir, int *x_dir)
{
	while (*angle < 0)
		*angle += 360;
	while (*angle >= 360)
		*angle -= 360;
	if (*angle >= 0 && *angle <= 90)
	{
		*y_dir = -1;
		*x_dir = 1;
	}
	if (*angle > 90 && *angle <= 180)
	{
		*y_dir = 1;
		*x_dir = -1;
	}
	if (*angle > 180 && *angle <= 270)
	{
		*y_dir = 1;
		*x_dir = -1;
	}
	if (*angle > 270 && *angle <= 360)
	{
		*y_dir = -1;
		*x_dir = 1;
	}
	// printf("dir y %d, dir x %d\n", *y_dir, *x_dir);
}

float	find_distance(t_data *data, int angle)
{
	int y_dir;
	int x_dir;
	
	
	float ori_y = data->p_y * SCALE;//origin
	float ori_x = data->p_x * SCALE;
	float y = ori_y;//moves through map
	float x = ori_x;
	
	angle_dirs(&angle, &y_dir, &x_dir);
	// todo depending on direction of ray, it can be one more pixel to any side (intercheck)
	

	int map_y = floor (y / SCALE);//coord in map
	int map_x = floor (x / SCALE);
		
	float y_step = 1 * y_dir;
	float x_step = 1 * tan(rad(angle)) * x_dir;
	//check for y = 0, x = 0, outside map
	while (data->map[map_y] && data->map[map_y][map_x] && data->map[map_y][map_x] != '1')
	{
		put_pixel(&data->frame, y, x, GREEN);
		//with angle -32, y needs to be y-2 for the distance fo be correct
		map_y = floor (y / SCALE);
		map_x = floor (x  / SCALE);
		y += y_step;//its going to high up for some reason
		x += x_step;
	}
	float dif_y = ori_y - y, dif_x = ori_x - x;
	float hyp = sqrt(pow(dif_y, 2) + pow(dif_x, 2));

	// printf("angle     %d\n", angle);
	// printf("origin y  %.2f\norigin x  %.2f\n", ori_y, ori_x);
	// printf("now y     %.2f\nnow x     %.2f\n", y, x);
	// printf("diff y    %.2f\ndiff x    %.2f\n", dif_y, dif_x);
	
	return (hyp);
}

void	draw_wall_section(t_data *data, float hyp, int angle, int i)
{
	// printf("angle %d, height %.4f\n", angle, hyp);
	int height = (int)"something";//yay fuck this stupid code
	//need to revert the height graph, basically has to be opposite.
	//closer things are bigger on screen
	int top = (data->win_height / 2) + (height / 2);
	int bot = (data->win_height / 2) - (height / 2);
	while (top < bot)
	{
		int y = 0;
		while (y < height)
		{
			put_pixel(&data->frame, y, top + i, RED);
			y++;
		}
		top++;
	}

}

void	draw_rays(t_data *data)//rename
{
	int i = data->win_width / 2;
	int angle = -32;
	while (i < data->win_width)
	{
		//check that hyp is already closest intersection
		float hyp = find_distance(data, angle);
		draw_wall_section(data, hyp, angle, i);
			
		
		
		i += 10;//this is the player_fov degree by degree, 20
		angle++;
		// float hyp = draw_single_ray(data, data->p_y, data->p_x, i);//angle wrong
		// draw_wall_section(data, hyp, i);
		// int j = 0;
		// while (j < data->win_height)
		// {
		// 	put_pixel(&data->frame, j, i, RED);
		// 	j++;
		// }
		// i++;
	}

	
	//old
	// int fov = 64;//forget fov, use screen size
	// int i = 0 - fov / 2;
	// while (i < fov / 2)
	// {
	// 	draw_single_ray(data, data->p_y, data->p_x, i);
	// 	i++;
	// }
	// int section = data->win_width / fov;
	// i = data->win_width / 2;
	// while (i < data->win_width)
	// {
	// 	if (i % section == 0 && i > data->win_width / 2)
	// 	{
	// 		// float hyp = draw_single_ray(data, data->p_y, data->p_x, i);//angle wrong
	// 		// draw_wall_section(data, hyp, i);
	// 		// int j = 0;
	// 		// while (j < data->win_height)
	// 		// {
	// 		// 	put_pixel(&data->frame, j, i, RED);
	// 		// 	j++;
	// 		// }
	// 	}
	// 	i++;
	// }	
	// draw_single_ray(data, data->p_y, data->p_x, 5);

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
				put_pixel(&data->frame, y, x, FLOOR);
			else
				put_pixel(&data->frame, y, x, CEILING);
			x++;
		}
		y++;
	}
}



int	main(int ac, char **av)
{
	t_data data;

	if (!init(ac, av, &data))
		return (clean_everything(&data), 1);

	create_background(&data);
	create_map(&data);
	draw_rays(&data);


	mlx_put_image_to_window(data.mlx, data.win, data.frame.img, 0, 0);
	mlx_key_hook(data.win, input, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
