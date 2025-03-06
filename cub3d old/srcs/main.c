/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/02/11 13:34:41 by bruno            ###   ########.fr       */
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

void	temp_screen_divider(t_data *data, int x)
{
	int y = 0;
	while (y <= data->frame->height)
	{
		put_pixel(data->frame, y, x, PINK);
		y++;
	}
}

float	y_mxc(int angle, int x, int c){
	return ((angle * x) + c);
}

void	raycast(t_data *data)
{
	float x = 0;//relative to player for now
	int angle = 45;
	printf("y = mx+c = %.2f\n", y_mxc(angle, x, 4));

	//screen divider
	// int screen_div = 8;
	// int x = 0;
	// while (x <= data->frame->width)
	// {
	// 	if (x % (data->frame->width / screen_div) == 0) {
	// 		temp_screen_divider(data, x);
	// 	}
	// 	x++;
	// }
}



int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	init(&data);
	
	// * this is useful for understanding the rays 
	// create_temp_screen(&data);
	raycast(&data);

	// make_minimap(&data);//not working, will remake
	mlx_put_image_to_window(data.mlx, data.win, data.frame->img, 0, 0);


	mlx_key_hook(data.win, handle_input, &data);
	mlx_hook(data.win, 17, 1L << 17, close_game, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
