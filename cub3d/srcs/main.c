/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/03/28 16:34:02 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	rad(int deg)
{
	return (deg * PI / 180);
}

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
		// put_pixel(&data->frame, y, x, GREEN);
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

//just drawing on half the screen for now
void	draw_wall_section(t_data *data, float hyp, int angle, int i)
{
	float dist_to_plane = (data->win_width / 2) / tan(rad(64) / 2);
	int height = SCALE * dist_to_plane / hyp;

	int top = (data->win_height / 2) - (height / 2);
	int bot = (data->win_height / 2) + (height / 2);
	
	int y = top;
	while (y < bot)
	{
		int x = 0;
		while (x < 20)
		{
			put_pixel(&data->frame, y, i + x, RED);
			x++;
		}
		y++;
	}

}

void	draw_rays(t_data *data)//rename
{
	int i = 0;
	int angle = -32;
	while (i < data->win_width)
	{
		//check that hyp is already closest intersection
		float hyp = find_distance(data, angle);
		draw_wall_section(data, hyp, angle, i);
			
		
		
		i += 20;//this is the player_fov degree by degree, 20
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
