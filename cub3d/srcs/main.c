/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/03/20 20:54:50 by bruno            ###   ########.fr       */
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

void	draw_player(t_data *data, int d_y, int d_x)
{
	d_y = d_y * SCALE;
	d_x = d_x * SCALE;
	//pixel
	put_pixel(&data->frame, d_y, d_x, GREEN);

	//draw a line
	//while loop starting where player is, and runs until y has changed by 1
	int angle = 90;//
	float f_y = (float)d_y;
	float f_x = (float)d_x;
	printf("y: %.2f\n", f_y);
	printf("x: %.2f\n", f_x);

	float desty;
	float destx;
	if (angle > 90 && angle < 180)//more checks xD
	{
		desty = f_y - 1 * SCALE;// this is + 30
		printf("dy: %.4f\n", desty);
		destx = f_y + 1 * SCALE / tan(rad(angle));
		printf("dx: %.4f\n", destx);
	}
	while (f_y > desty)//find another way for this loop
	{
		// put_pixel(&data->frame, (int)f_y, (int)f_x, GREEN);
		f_y -= 1;
		f_x += 1 / tan(rad(angle));
	}

	
	// angle = 20;
	// f_y = (float)d_y;
	// f_x = (float)d_x;
	// printf("y: %.2f\n", f_y);
	// printf("x: %.2f\n", f_x);
	// desty = f_y + 1 * SCALE;// this is + 30
	// printf("dy: %.4f\n", desty);
	// destx = f_y + 1 * SCALE / tan(rad(angle));
	// printf("dx: %.4f\n", destx);
	// while (f_y < desty)
	// {
	// 	put_pixel(&data->frame, (int)f_y, (int)f_x, GREEN);
	// 	f_y += 1;
	// 	f_x += 1  / tan(rad(angle));
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
				put_pixel(&data->frame, y * SCALE, x * SCALE, GREEN);
				// draw_player(data, y, x);
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
