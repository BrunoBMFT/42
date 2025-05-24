/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:49:30 by brfernan          #+#    #+#             */
/*   Updated: 2025/05/12 15:02:20 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	put_pixel(t_data *data, int y, int x, int color)
{
	char	*offset;

	if (y < 0 || x < 0 || y > data->win_height || x > data->win_width)
		return ;
	offset = data->frame.addr + (y * data->frame.line_len + x
			* (data->frame.bits_per_pixel / 8));
	*(unsigned int *)offset = color;
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
	create_background(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
}
