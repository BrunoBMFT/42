/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/03/21 19:37:10 by bruno            ###   ########.fr       */
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

float	rad(int deg)
{
	return (deg * PI / 180);
}

void	draw_ray(t_data *data, int d_y, int d_x, int angle)
{
	d_y = d_y * SCALE;
	d_x = d_x * SCALE;

	float f_y = (float)d_y;
	float f_x = (float)d_x;

	//decide direction
	int y_dir;
	int x_dir;
	//dont forget loops or negatives
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
	while (data->map[y][x] != '1')//this loop will end at map[y][x] == 1
	{
		y = (int)round(f_y) / SCALE;
		x = (int)round(f_x) / SCALE;
		put_pixel(&data->frame, (int)f_y, (int)f_x, GREEN);
		f_y += 1 * y_dir;
		f_x += 1 * tan(rad(angle)) * x_dir;//tan 90 is infinite
	}


	// f_y = (float)d_y;
	// f_x = (float)d_x;
	// while (data->map[y][x] != '1')//this loop will end at map[y][x] == 1
	// {
	// 	y = (int)round(f_y) / SCALE;
	// 	x = (int)round(f_x) / SCALE;
	// 	put_pixel(&data->frame, (int)f_y, (int)f_x, GREEN);
	// 	f_x += 1 * x_dir;
	// 	f_y += 1 / tan(rad(angle)) * y_dir;
	// }
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
				put_pixel(&data->frame, y * SCALE, x * SCALE, GREEN);
				draw_ray(data, y, x, 87);
				// int i = 0;
				// while (i < 360)
				// {
				// 	if (i % 90)
				// 		draw_ray(data, y, x, i);
				// 	i++;
				// }
			}
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

	create_map(&data);

	mlx_put_image_to_window(data.mlx, data.win, data.frame.img, 0, 0);
	mlx_key_hook(data.win, input, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
