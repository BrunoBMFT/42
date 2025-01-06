/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/01/06 04:11:56 by bruno            ###   ########.fr       */
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

int	get_pixel(t_img *img, int y, int x)
{
	char	*dst;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	put_pixel(t_img *img, int y, int x, int color)
{
	char	*offset;
	offset = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}

//! ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//! ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//	decide a size for minimap (still have to decide how to take care of different shaped maps, size always the same, but pixels different size)
//	then, change the main loop to loop through the map instead, and to then save to the minimap img
//			(for this to work, dont forget to change make_minimap_pixel to put pixel onto minimap img)
//! ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//! ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void	make_frame(t_data *data, t_img *img, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			int color = get_pixel(img, i, j);
			put_pixel(data->frame, i + y, j + x, color);
			j++;
		}
		i++;
	}
}

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

void	create_player(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		error(data, "Minimap player creation failed");
	data->player->color = GREEN;
	int y = 0;
	while (data->map[y])
	{
		int x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NESW", data->map[y][x]))
			{
				data->player->y = y;
				data->player->x = x;
			}
			x++;
		}
		y++;
	}
}

int	handle_move(t_data *data)
{
	make_minimap(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	init(&data);
//todo create a function that creates images from any source to any destination
	// make_frame(&data, data.texture->north, 0, 0);//works
	
	create_player(&data);
	create_temp_screen(&data);

	make_minimap(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.frame->img, 0, 0);


	mlx_key_hook(data.win, handle_input, &data);
	mlx_hook(data.win, 17, 1L << 17, close_game, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
