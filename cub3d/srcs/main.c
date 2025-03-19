/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/03/19 02:47:32 by bruno            ###   ########.fr       */
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

void	draw_player(t_data *data, int y, int x)
{
	put_pixel(&data->frame, y * SCALE, x * SCALE, GREEN);
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
				draw_player(data, y, x);
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
