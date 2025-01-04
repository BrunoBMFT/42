/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/01/04 00:05:01 by bruno            ###   ########.fr       */
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
	//! instead, make it a fixed size, and the pixels themselves change size depending on map size
	//TODO find better logic
	//knowing max length of line for calc
	int max_len = 0;
	int i = 0;
	while (data->map[i])
	{
		int temp = ft_strlen(data->map[i]);
		if (max_len < temp)
			max_len = temp;
		i++;
	}
	//knowing max length of line for calc
	//TODO find better logic
	//make so the size of the actual image is the same?
	//SIZE OF THE IMG ISNT CORRECT, STUFF AT ALMOST THE END IS NOT SAVED IN THE IMG ITSELF
	data->minimap->width = max_len * 30;//fix size to map size, for now like this to test
	data->minimap->height = ft_split_wordcount(data->map) * 30;//fix size to map size, for now like this to test
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

void	make_minimap_pixel(t_data *data, int y, int x, int color)//change to put_pixel to minimap img
{
	put_pixel(data->frame, y, x, color);
	int i = 0;
	while (i < 20)
	{
		int j = 0;
		while (j < 20)
		{
			put_pixel(data->frame, i + y, j + x, color);
			j++;
		}
		i++;
	}
}



//! ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//! ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//! ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

//	have to decide a way to have a scale in make_minimap_pixel and in the loop of data.frame.height
//	decide a size for minimap, and make it so that the scale changes depending on the size of the map
//	then, change the main loop to loop through the map instead, and to then save to the minimap img
//			(for this to work, dont forget to change make_minimap_pixel to put pixel onto minimap img)
//	also, later, make borders for the pixels in the minimap so you can tell where one ends and another starts

//! ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//! ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//! ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	init(&data);
	// make_frame(&data, data.texture->north, 0, 0);//works

//make an image with this background loop, then make minimap image on top
	// int y = 0;
	// while (y <= data.frame->height)
	// {
	// 	int x = 0;
	// 	while (x <= data.frame->width)
	// 	{
	// 		put_pixel(data.frame, y, x, 1000);
	// 		x++;
	// 	}
	// 	y++;
	// }
//create a function that creates images from any source to any destination
//  easier management of minimap if i can put everything inside minimap img
//	and then just scale it for what i need


	int y = 0;
	int i = 0;
	while (i < data.frame->height)
	{
		int j = 0;
		int x = 0;
		while (j < data.frame->width)
		{
			if (data.map[y] && data.map[y][x])
			{
// todo this scale is weird
				if (data.map[y][x] == '1')
					make_minimap_pixel(&data, y * 50, x * 50, 111111);//green
				if (data.map[y][x] == '0')
					make_minimap_pixel(&data, y * 50, x * 50, 1111);//dark blue
				if (data.map[y][x] == 'N')
					make_minimap_pixel(&data, y * 50, x * 50, 110000);//dark blue
				else
					make_minimap_pixel(&data, y * 50, x * 50, 11111111);//pink
				x++;
			}
			else
			{
				put_pixel(data.frame,  data.frame->height / 2, j, 110000);
				put_pixel(data.frame, i, data.frame->width / 2, 110000);
				put_pixel(data.frame,  data.frame->height / 3, j, 110000);
				put_pixel(data.frame, i, data.frame->width / 3, 110000);
				put_pixel(data.frame,  data.frame->height / 3 + data.frame->height / 3, j, 110000);
				put_pixel(data.frame, i, data.frame->width / 3 +  data.frame->width / 3, 110000);
			}
			j++;
		}
		if (data.map[y])
			y++;
		i++;
	}


//this commented code saves into minimap img and puts it into the frame
//	for this to work, dont forget to change make_minimap_pixel to put pixel onto minimap img
	// y = 0;
	// while (data.map[y])
	// {
	// 	int x = 0;
	// 	while (data.map[y][x])
	// 	{
	// 		// if (data.map[y][x] != ' ')
	// 		// 	make_minimap_pixel(&data, y, x, 111111);
	// 		if (data.map[y][x] == '1')
	// 			make_minimap_pixel(&data, y, x, 111111);//green
	// 		if (data.map[y][x] == '0')
	// 			make_minimap_pixel(&data, y, x, 1111);//dark blue
	// 		else
	// 			make_minimap_pixel(&data, y, x, 11111111);//pink
	// 		x++;
	// 	}
	// 	y++;
	// }
	// make_frame(&data, data.minimap, 0, 0);
	

	
	mlx_put_image_to_window(data.mlx, data.win, data.frame->img, 0, 0);

	mlx_key_hook(data.win, handle_input, &data);
	mlx_hook(data.win, 17, 1L << 17, close_game, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
