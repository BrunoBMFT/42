/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2024/12/23 03:11:41 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//minimap
//need to find a way to only put it somewhere on the map
//also, want to find a simple way to change it position in the game
//   like having it at top right, bottom left

void	init_frame(t_data *data, int x, int y)
{
	data->frame = malloc(sizeof(t_img));//ugly code from here
	if (!data->frame)
		error(data, "Frame image allocation failed");
	data->frame->width = x / 2;
	data->frame->height = y / 2;
	data->frame->img = mlx_new_image(data->mlx, data->frame->width, data->frame->height);
	if (!data->frame->img)
		error(data, "Frame image failed");
	data->frame->addr = mlx_get_data_addr(data->frame->img, &data->frame->bits_per_pixel,
			&data->frame->line_len, &data->frame->endian);//ugly code to here
}

void	init_minimap(t_data *data, int x, int y)
{
	data->minimap = malloc(sizeof(t_img));//ugly code from here
	if (!data->minimap)
		error(data, "Minimap image allocation failed");
	data->minimap->width = x / 4;
	data->minimap->height = y / 4;
	data->minimap->img = mlx_new_image(data->mlx, data->minimap->width, data->minimap->height);
	if (!data->minimap->img)
		error(data, "Minimap image failed");
	data->minimap->addr = mlx_get_data_addr(data->minimap->img, &data->minimap->bits_per_pixel,
			&data->minimap->line_len, &data->minimap->endian);//ugly code to here
}

void	init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error(data, "Mlx init failed");

	init_textures(data);

	int x, y;
	mlx_get_screen_size(data->mlx, &x, &y);
	data->win = mlx_new_window(data->mlx, x / 2, y / 2, "cub3d");
	if (!data->win)
		error(data, "Window failed to open");
	
	init_frame(data, x, y);
	init_minimap(data, x, y);
}

// int	get_pixel(t_img *img, int x, int y)
// {
// 	char	*dst;
// 	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
// 	return (*(unsigned int *)dst);
// }

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*offset;
	offset = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}

void	make_minimap_pixel(t_data *data, int color, int x, int y)//this make_img is good for 2d, so i can use it prob for minimap
{
	int				i;
	int				j;

	i = 0;
	printf("frame width: %d\nframe height: %d\n", data->frame->width, data->frame->height);
	printf("minimap width: %d\nminimap height: %d\n", data->minimap->width, data->minimap->height);
	while (i < data->minimap->width)//find better way to not go out of bounds?
	{
		j = 0;
		while (j < data->minimap->height)//find better way to not go out of bounds?
		{
			put_pixel(data->minimap, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	init(&data);

	// make_img(&data, data.texture->north, 0, 0);

	int y = 0;
//everything is tripping, have to normalise a screen size, possible will hard code it to a specific resolution
	while (data.map[y])
	{
		int x = 0;
		while (data.map[y][x])
		{
			if (data.map[y][x] == 0)
				make_minimap_pixel(&data, 111111, x, y);
			else if (data.map[y][x] == 0)
				make_minimap_pixel(&data, 110011, x, y);
			else if (ft_strchr("NESW", data.map[y][x]))
				make_minimap_pixel(&data, 110011, x, y);
			x++;
		}
		y++;
	}



	
	mlx_put_image_to_window(data.mlx, data.win, data.frame->img, 0, 0);

	mlx_key_hook(data.win, handle_input, &data);
	mlx_hook(data.win, 17, 1L << 17, close_game, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
