/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/01/06 18:01:16 by bruno            ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	init(&data);
	
	// * this is useful for understanding the rays 
	create_temp_screen(&data);


	make_minimap(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.frame->img, 0, 0);


	mlx_key_hook(data.win, handle_input, &data);
	mlx_hook(data.win, 17, 1L << 17, close_game, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
