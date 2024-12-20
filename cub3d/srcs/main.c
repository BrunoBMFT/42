/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2024/12/20 10:33:56 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
//decide if i do like it is now, or like so long (boolean returns)

//minimap
//need to find a way to only put it somewhere on the map
//also, want to find a simple way to change it position in the game
//   like having it at top right, bottom left
// void	add_coord(t_data *data, int y, int x)
// {
// 	//need a img init, to save to the img the color
// 	//the img is what is gonna be each frame
// 	//i need to find color values for the minimap and decide where to put it
// }
// void	create_minimap(t_data *data)
// {
// 	int y = 0;
// 	while (data->map[y])
// 	{
// 		int x = 0;
// 		while (data->map[y][x])
// 		{
// 			add_coord(data, y, x);//get a way to choose the color here
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error(data, "Mlx init failed");

	//have the access check for all happen before allocating
	if (access(data->p_north, R_OK))
		error(data, "North texture not found");
	if (access(data->p_east, R_OK))
		error(data, "East texture not found");
	if (access(data->p_south, R_OK))
		error(data, "South texture not found");
	if (access(data->p_west, R_OK))
		error(data, "West texture not found");

	
	data->texture = malloc(sizeof(t_img) * 4);
	if (!data->texture)
		error(data, "Error allocating memory for textures");
	data->texture->north = NULL;
	data->texture->east = NULL;
	data->texture->south = NULL;
	data->texture->west = NULL;
	
	data->texture->north = malloc(sizeof(t_img));
	if (!data->texture->north)
		error(data, "Error allocating memory for north");
	data->texture->north->img = mlx_xpm_file_to_image(data->mlx, data->p_north, 
				&data->texture->north->width, &data->texture->north->height);
	if (!data->texture->north->img)
		error(data, "Image failed to open");
	data->texture->north->addr = mlx_get_data_addr(data->texture->north->img, 
	&data->texture->north->bits_per_pixel, &data->texture->north->line_len, &data->texture->north->endian);


	
	// data->texture->east = malloc(sizeof(t_img));
	// data->texture->south = malloc(sizeof(t_img));
	// data->texture->west = malloc(sizeof(t_img));

	int x, y;
	mlx_get_screen_size(data->mlx, &x, &y);//check if it isnt too big
	data->win = mlx_new_window(data->mlx, x / 2, y / 2, "cub3d");
	if (!data->win)
		error(data, "Window failed to open");
	
	mlx_put_image_to_window(data->mlx, data->win, data->texture->north->img, 0, 0);



	//test
	// data->frame = malloc(sizeof(t_img));
	// if (!data->frame)
	// 	error(data, "Failed to allocate memory for frame");
	// data->frame->img = mlx_xpm_file_to_image(data->mlx, "./sprites/west.xpm", &data->frame->width, &data->frame->height);
	// if (!data->frame->img)
	// 	error(data, "Image failed to open");
	// data->frame->addr = mlx_get_data_addr(data->frame->img, &data->frame->bits_per_pixel, &data->frame->line_len, &data->frame->endian);
	//test
}

// int	get_pixel(t_img *img, int x, int y)
// {
// 	char	*dst;
// 	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
// 	return (*(unsigned int *)dst);
// }
// void	put_pixel(t_img *img, int x, int y, int color)
// {
// 	char	*offset;
// 	offset = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
// 	*(unsigned int *)offset = color;
// }
// void	make_img(t_data *data)
// {
// 	int				i;
// 	int				j;
// 	unsigned int	color;
// 	i = 0;
// 	while (i < data->frame->height)
// 	{
// 		j = 0;
// 		while (j < data->frame->width)
// 		{
// 			color = get_pixel(data->frame, i, j);
// 			put_pixel(data->frame, i, j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// 	mlx_put_image_to_window(data->mlx, data->win, data->frame->img, 0, 0);
// }

int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	init(&data);

	// create_minimap(&data);
	
	// mlx_put_image_to_window(data.mlx, data.win, data.frame->img, 0, 0);


	mlx_key_hook(data.win, handle_input, &data);
	mlx_hook(data.win, 17, 1L << 17, close_game, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
