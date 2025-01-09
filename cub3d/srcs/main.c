/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/01/09 02:38:11 by bruno            ###   ########.fr       */
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

float	adj(float n, int angle)
{
	return (1);
}

float	opp(float n, int angle)
{
	return (1);
}

float	hyp(float n, int angle)
{
	return (1);
}

float square(float n)//degrees to radians
{
	return (n * n);
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

// !
// testing
// 360 / 5 = 72
//expected hypotenuse horizontal results:
//72  6.4721
//144 3.7082
//216 
//288
//360
// !



//need center cause there where ill raycast from
void	raycast(t_data *data)//make a function that does the return for the distance, to test if it is working
{
	int screen_div = 8;
	float y_center = (data->player->y * data->pixel_size) + (data->player->size / 2);
	float x_center = (data->player->x * data->pixel_size) + (data->player->size / 2);
	// printf("pixel size %d\n", data->pixel_size);
	// printf("player:\nlocation y: %.2f, x: %.2f\nsize %d\n", data->player->y, data->player->x, data->player->size);
	// printf("coord in map %.2f %.2f\n", data->player->y, data->player->x);
	// printf("coord in map %.2f %.2f\n", data->player->y * data->pixel_size, data->player->x * data->pixel_size);
	// printf("center pixel %.2f %.2f\n", y_center, x_center);
	// printf("center coord %.2f %.2f\n", y_center / data->pixel_size, x_center / data->pixel_size);
	//divide 360 by 8 and check every final distance
	//right now, its assuming the center is at the int value
	int x = 0;
	int degree = 12;//! until 45 it seems like it works, test more
	float rad = deg_to_rad(degree);
	// printf("deg %d -> rad %f\n", degree, rad);
	
	// * also, will need to decide direction, since the way things are sent and the way the roundf gets done is based on that
	bool	hit = false;
	float temp_y = y_center;
	float temp_x = x_center;
	while (!hit)
	{
		// printf("y: %.2f, x: %.2f \n", temp_y / data->pixel_size, temp_x / data->pixel_size);
		int y = (int)roundf(temp_y - 1) / data->pixel_size;//-1 so it checks above, although it feels weird checking like this
		int x = (int)roundf(temp_x) / data->pixel_size;
		if (x < 0 || x > data->max_len || y < 0 || y > ft_split_wordcount(data->map))
			/* printf("over limit, prob will find with other loop\n"); */ break ;
		// printf("testing y %d, x %d\n", y, x);
		if (data->map[y][x] == '1')
			break ;

		//this part is actually simpler than i thought, cause sin (x) = y   &&   sin(360 - x) = -y
		//basically rotations are taken care of by the tryg functions themselves, at least it seems
		float diff = tan(rad);
		temp_x += diff * data->pixel_size;
		temp_y -= data->pixel_size;
	}
	// printf("distance y %.2f, x %.2f \n", (y_center - temp_y) / data->pixel_size, (x_center - temp_x) / data->pixel_size);
	float distance1 = ((y_center - temp_y) / data->pixel_size) / cos(rad);
	printf("horizontal distance %f\n", distance1);
	// * final distance by 12 degrees is 2.0446811897 horizontal line
	// * final distance by 24 degrees is 2.189272557 horizontal line

	temp_y = y_center;
	temp_x = x_center;
	while (!hit)
	{
		// printf("y: %.2f, x: %.2f \n", temp_y / data->pixel_size, temp_x / data->pixel_size);
		int x = (int)roundf(temp_x) / data->pixel_size;
		int y = (int)roundf(temp_y + 1) / data->pixel_size;
		if (x < 0 || x > data->max_len || y < 0 || y > ft_split_wordcount(data->map))
			/* printf("over limit, prob will find with other loop\n"); */ break ;
		// printf("testing y %d, x %d\n", y, x);
		if (data->map[y][x] == '1')
			break ;

		//this part is actually simpler than i thought, cause sin (x) = y   &&   sin(360 - x) = -y
		//basically rotations are taken care of by the tryg functions themselves, at least it seems
		float diff = 1 / tan(rad);
		temp_y -= diff * data->pixel_size;
		temp_x += data->pixel_size;
	}
	// printf("distance y: %.4f, x: %.2f \nangle: %d\n", (temp_y - y_center) / data->pixel_size, (temp_x - x_center) / data->pixel_size, degree);
	float distance2 = ((temp_x - x_center) / data->pixel_size) / sin(rad);
	printf("vertical distance %f\n", distance2);
	// * final distance by 12 degrees is 4.8097
	// * final distance by 24 degrees is 2.4585
	float final;
	if (distance1 < distance2)
		final = distance1;
	else
		final = distance2;
	printf("closest distance at %d degrees is %f\n", degree, final);
		

// i think the way im checking if it hit a part of the map or not is wrong, since it doesnt account
// for angles. possibly will need to check each int in map to see if it is a '1' or not
// so basically i need to find the distance from center to int, and then from int to int at an angle?





// ! from here down, pure and utter confusion
// i have the angle for the first and 2nd, which is 0 and 12 degrees starting from north
// 	i supposedly can save the y and x distance, by measuring how many loops were needed, since
// 	the jump y and x do is based of the angle that is being run
// by have that y and x distance + the angle, simple sohcahtoa should get me the hypotenuse, right?
// that hypotenuse is what decides the size of the line that will be drawn on screen

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
