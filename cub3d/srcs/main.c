/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/03/25 20:41:56 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	input(int keysym, t_data *data)
{
	if (keysym == XK_Escape){	
		clean_everything(data);
		exit(0);
	}
	return (0);
}

void	put_pixel(t_img *img, int y, int x, int color)//put a limit for size? like if (y > win_width)
{
	char	*offset;

	// if (y < 0 || y > img->height || x < 0 || x > img->width){
	// 	// printf("tried to put pixel outside image\n");
	// 	return ;
	// }
	offset = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}

void	loop_map(t_data *data, int y, int x, int color)
{
	int	i = 0;
	while (i < SCALE)
	{
		int j = 0;
		while (j < SCALE)
		{
			//find better way for pixels, maybe make the scale onto put_pixel itself?
			put_pixel(&data->frame, (y * SCALE) + i, (x * SCALE) + j, color);
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
			else if (data->map[y][x] == '0')
				loop_map(data, y, x, GREY);
			else if (ft_strchr("NESW", data->map[y][x]))
			{
				put_pixel(&data->frame, y, x, GREEN);
				data->p_y = y;
				data->p_x = x;
			}
			x++;
		}
		y++;
	}
}

float	rad(int deg)
{
	return (deg * PI / 180);
}

void	draw_wall_section(t_data *data, float hyp, int angle)
{
	//section start and end need to be calculated using the angle that was sent
	int section_start = data->win_width / 2 + angle * 20;
	int section_end = data->win_width / 2 + angle * 20 + data->win_width / 64;
	int x = 0;
	hyp = hyp * -1;//to test, will put hyp to positive
	while (x + section_start < section_end)
	{
		int line_size = data->win_height - (int)hyp;//roundf?
		int start = 0;
		//have it centered
		while (start < line_size / 2)
		{
			put_pixel(&data->frame, start, x + section_start, RED);
			start++;
		}
		x++;
	}
}
//seems like its not giving the correct results
//starting from angle 0, the difference between each distance should be increasing
//it doesnt seem to do that, maybe fabs will help?
float	draw_single_ray(t_data *data, int d_y, int d_x, int angle)
{
	d_y = d_y * SCALE;
	d_x = d_x * SCALE;

	float f_y = (float)d_y;
	float f_x = (float)d_x;
	float ori_y = f_y;
	float ori_x = f_x;

	//decide direction
	int y_dir;
	int x_dir;
	//dont forget loops or negatives
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	if (angle >= 0 && angle <= 90)
	{
		y_dir = -1;
		x_dir = 1;
	}
	if (angle > 90 && angle <= 180)
	{
		y_dir = 1;
		x_dir = -1;
	}
	if (angle > 180 && angle <= 270)
	{
		y_dir = 1;
		x_dir = -1;
	}
	if (angle > 270 && angle <= 360)
	{
		y_dir = -1;
		x_dir = 1;
	}
	
	//draw ray
	int y = (int)round(f_y) / SCALE;
	int x = (int)round(f_x) / SCALE;
	while (data->map[y][x] != '1')
	{
		put_pixel(&data->frame, (int)f_y, (int)f_x, GREEN);
		y = (int)round(f_y) / SCALE;
		x = (int)round(f_x) / SCALE;
		if ((angle > 45 && angle < 135) || (angle > 225 && angle < 315))
		{
			f_x += 1 * x_dir;
			f_y += 1 / tan(rad(angle)) * y_dir;//tan 90 is infinite
		}
		else
		{
			f_y += 1 * y_dir;
			f_x += 1 * tan(rad(angle)) * x_dir;//tan 90 is infinite
		}
	}
	float hyp = (ori_x - f_x) / sin(rad(angle));
	// printf("%.4f\n", hyp);
	//i have the original coordinates, the new coordinates and the angle
	//all i need if the hypotenuse, with that, i just draw like that.
	//still need to learn the theorem or whatever it is

	return (hyp);
	draw_wall_section(data, hyp, angle);
}

void	draw_rays(t_data *data)
{
	int fov = 64;

	int i = 0 - fov / 2;
	while (i < fov / 2)
	{
		float hyp = draw_single_ray(data, data->p_y, data->p_x, i);
		if (i >= 0)
			printf("%.2f\n", hyp);
		i++;
	}
	printf("rays drawn in map %d\n", i + fov / 2);



	int section = data->win_width / fov;
	printf("sections %d\n", section);
	i = data->win_width / 2;
	int count = 0;
	while (i < data->win_width)
	{
		if (i % section == 0 && i > data->win_width / 2)
		{
			float hyp = draw_single_ray(data, data->p_y, data->p_x, count);//angle wrong
			printf("%.2f\n", hyp);
			draw_wall_section(data, hyp, count);
			count++;
			int j = 0;
			while (j < data->win_height)
			{
				put_pixel(&data->frame, j, i, RED);
				j++;
			}
		}
		i++;
	}
	printf("sections counted %d\n", count);
	//should be half of rays drawn since we are starting midway

	
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
