/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:02:49 by bruno             #+#    #+#             */
/*   Updated: 2025/03/28 17:31:19 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//have a putpixel for frame and one for other images?
void	put_pixel(t_data *data, int y, int x, int color)
{
	char	*offset;

	if (y < 0 || x < 0 || y > data->win_height || x > data->win_width)//check if its correct
	{
		printf("putpixel outofbounds\n");
		return ;
	}
	offset = data->frame.addr + (y * data->frame.line_len + x * (data->frame.bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}

//find better way for pixels, maybe make the scale onto put_pixel itself?
void	loop_map(t_data *data, int y, int x, int color)
{
	int	i = 0;
	while (i < SCALE)
	{
		int j = 0;
		while (j < SCALE)
		{
			put_pixel(data, (y * SCALE) + i, (x * SCALE) + j, color);
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
				put_pixel(data, y, x, GREEN);
			x++;
		}
		y++;
	}
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
				put_pixel(data, y, x, FLOOR);
			else
				put_pixel(data, y, x, CEILING);
			x++;
		}
		y++;
	}
}

void	clear_img(t_data *data)
{
	create_background(data);
}

int	input(int keysym, t_data *data)
{
	if (keysym == XK_Escape){	
		clean_everything(data);
		exit(0);
	}
	if (keysym == 'w'){
		data->p_y -= 0.5;
		clear_img(data);
		draw_rays(data);
		mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);

	}
	if (keysym == 's'){
		data->p_y += 0.5;
		clear_img(data);
		draw_rays(data);
		mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);

	}

	if (keysym == 'a'){
		data->p_x -= 0.5;
		clear_img(data);
		draw_rays(data);
		mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
	}


	if (keysym == 'd'){
		data->p_x += 0.5;
		clear_img(data);
		draw_rays(data);
		mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
	}
	return (0);
}
