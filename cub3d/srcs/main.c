/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/01/08 03:01:09 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	create_temp_screen(t_data *data)
{
	//makes an image with this background loop, then makes minimap image on top
	int y = 0;
	while (y <= data->frame->height)
	{
		int x = 0;
		while (x <= data->frame->width)
		{
			if (x % 30 == 0)
				put_pixel(data->frame, y, x, PINK);
			else
				put_pixel(data->frame, y, x, GREY);
			x++;
		}
		y++;
	}
}

float deg_to_rad(float n)//degrees to radians
{
	return (n * PI / 180);
}

float	find_distance(t_data *data)
{
	float	y_dist = 0;
	float	x_dist = 0;
	return (y_dist + x_dist);
}
void	temp_screen_divider(t_data *data, int x)
{
	int y = 0;
	while (y <= data->frame->height)
	{
		put_pixel(data->frame, y, x, PINK);
		y++;
	}
}
//need center cause there where ill raycast from
void	raycast(t_data *data)
{
	int screen_div = 8;
	float y_center = (data->player->y * data->pixel_size) + (data->player->size / 2);
	float x_center = (data->player->x * data->pixel_size) + (data->player->size / 2);
	printf("pixel size %d\n", data->pixel_size);
	printf("player:\nlocation y: %.2f, x: %.2f\nsize %d\n", data->player->y, data->player->x, data->player->size);
	printf("coord in map %.2f %.2f\n", data->player->y, data->player->x);
	printf("coord in map %.2f %.2f\n", data->player->y * data->pixel_size, data->player->x * data->pixel_size);
	printf("center pixel %.2f %.2f\n", y_center, x_center);
	printf("center coord %.2f %.2f\n\n", y_center / data->pixel_size, x_center / data->pixel_size);


	//need to draw a line from pixel 81 in an angle and keep sending it forward until pixel / pixelsize in map == '1'
	int x = 0;
	int angle = 0;//forward
	
	bool	hit = false;
	float y_ray = y_center;
	float x_ray = x_center;
	int temp_y = (int)roundf(y_ray);
	int temp_x = (int)roundf(x_ray);
	while (!hit)
	{
		temp_y = (int)roundf(y_ray) / data->pixel_size;
		temp_x = (int)roundf(x_ray) / data->pixel_size;
		printf("y %d x%d \n", temp_y, temp_x);
		if (data->map[temp_y][temp_x] == '1'){
			hit = true;
		}
		y_ray -= data->pixel_size;//protect out of bounds
	}
	printf("hit at y %d x%d \n", temp_y, temp_x);

// i think the way im checking if it hit a part of the map or not is wrong, since it doesnt account
// for angles. possibly will need to check each int in map to see if it is a '1' or not
// so basically i need to find the distance from center to int, and then from int to int at an angle?

// ! from here down, pure and utter confusion
// i have the angle for the first and 2nd, which is 0 and 12 degrees starting from north
// 	i supposedly can save the y and x distance, by measuring how many loops were needed, since
// 	the jump y and x do is based of the angle that is being run
// by have that y and x distance + the angle, simple sohcahtoa should get me the hypotenuse, right?
// that hypotenuse is what decides the size of the line that will be drawn on screen


	//tryg
	float distance = tan(0);
	printf("distance %.4f\n", distance);

	// angle += 12;
	// while (!hit)
	// {

		
	// 	printf("before y %.2f x%.2f \n", y_ray, x_ray);
	// 	temp_y = (int)roundf(y_ray) / data->pixel_size;
	// 	temp_x = (int)roundf(x_ray) / data->pixel_size;
	// 	printf("y %d x%d \n", temp_y, temp_x);
	// 	if (data->map[temp_y][temp_x] == '1'){
	// 		hit = true;
	// 	}
	// 	y_ray -= data->pixel_size;//here tryg
	// }
	// printf("hit at y %d x%d \n", temp_y, temp_x);

	while (x <= data->frame->width)//this is rays
	{
		if (x % (data->frame->width / screen_div) == 0) {
			temp_screen_divider(data, x);
			// float distance = find_distance(data);



			// angle = 0;
			// printf("distance %f\n", distance);	
			//while (i < distance)
			//	while (x < fov_slice)
			//		putpixels
			//
			//
			//
			//
			//
		}
		x++;
	}
}


int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	init(&data);
	
	// * this is useful for understanding the rays 
	// create_temp_screen(&data);
	raycast(&data);

	make_minimap(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.frame->img, 0, 0);


	mlx_key_hook(data.win, handle_input, &data);
	mlx_hook(data.win, 17, 1L << 17, close_game, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
