/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/03/31 22:00:05 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	rad(int deg)
{
	return (deg * PI / 180);
}

//this isnt really used to its power, and is bad
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

//do 2 functions, one for h inter, and one for v inters
float	find_distance(t_data *data, int angle)
{
	//decide angles and steps
	int y_dir, x_dir;
	angle_dirs(&angle, &y_dir, &x_dir);
	
	
	float ori_y = data->p_y * SCALE, ori_x = data->p_x * SCALE;//origin
	float y = ori_y, x = ori_x;//moves through map
	
	// depending on direction of ray, it can be one more pixel to any side (intercheck)
	

	int map_y = floor (y / SCALE);//coord in map
	int map_x = floor (x / SCALE);

	float y_step, x_step;
	// y_step = 1 * y_dir;
	// x_step = 1 * tan(rad(angle)) * x_dir;
	if ((angle > 315 && angle < 360) || (angle > 0 || angle <= 45) ||
		(angle > 135 && angle <= 225)){
		y_step = 1 * y_dir;
		x_step = 1 * tan(rad(angle)) * x_dir;
	}
	else if ((angle > 45 && angle <= 135) || (angle > 225 && angle <= 315)){
		x_step = 1 * x_dir;
		y_step = 1 / tan(rad(angle)) * y_dir;
	}
	
	put_pixel(data, y, x, GREEN);
	
	//check for y = 0, x = 0, outside map
	while (data->map[map_y] && data->map[map_y][map_x] && data->map[map_y][map_x] != '1')
	{
		//with angle -32, y needs to be y-2 for the distance fo be correct
		map_y = floor (y / SCALE);
		map_x = floor (x  / SCALE);
		y += y_step;//its going to high up for some reason
		x += x_step;
		put_pixel(data, y, x, GREEN);
	}
	float dif_y = ori_y - y, dif_x = ori_x - x;
	float hyp = sqrt(pow(dif_y, 2) + pow(dif_x, 2));
	return (hyp);
}

void	draw_wall_section(t_data *data, float hyp, int angle, int i)
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

void	draw_rays(t_data *data)//rename
{
	int i = 0;
	//angle related to fov
	int angle = data->p_angle - 32;//related to facing angle
	printf("%d\n", data->p_angle);
	while (i < data->win_width)
	{
		//do a h_inter and a v_inter
		float hyp = find_distance(data, angle);
		draw_wall_section(data, hyp, angle, i);
		
		
		
		i += 20;//this is the player_fov degree by degree, 20
		angle++;
	}
}



int	main(int ac, char **av)
{
	t_data data;

	if (!init(ac, av, &data))
		return (clean_everything(&data), 1);
	data.p_angle = 0;
	create_background(&data);
	create_map(&data);
	draw_rays(&data);


	mlx_put_image_to_window(data.mlx, data.win, data.frame.img, 0, 0);
	mlx_key_hook(data.win, input, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
