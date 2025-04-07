/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:49:30 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/07 19:48:24 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clear_img(t_data *data)
{
	create_background(data);
}

void	create_background(t_data *data)
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
				put_pixel(data, y, x, data->color_floor);
			else
				put_pixel(data, y, x, data->color_ceiling);
			x++;
		}
		y++;
	}
}

void	create_frame(t_data *data)
{
	clear_img(data);
	raycast(data);
	create_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
}
