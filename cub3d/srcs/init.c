/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:04:14 by bruno             #+#    #+#             */
/*   Updated: 2025/03/18 18:10:50 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_variables(t_data *data)
{
	data->file = NULL;
	data->map = NULL;
	data->p_north = NULL;
	data->p_east = NULL;
	data->p_south = NULL;
	data->p_west = NULL;
	data->c_floor = NULL;
	data->c_ceiling = NULL;
	//find better place
	data->mlx = NULL;
	data->win = NULL;
	data->north.img = NULL;
	data->east.img = NULL;
	data->south.img = NULL;
	data->west.img = NULL;
	data->frame.img = NULL;
}

bool	init_texture_img(t_data *data, t_img *texture, char *img_src)
{
	texture->img = NULL;
	texture->img = mlx_xpm_file_to_image(data->mlx,
		img_src, &texture->width, &texture->height);
	if (!texture->img)
		return (error("A image failed to init"));
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, 
		&texture->line_len, &texture->endian);
	if (!texture->addr)
		return (error("An image address failed init"));
	return (true);
}

bool	init_imgs(t_data *data)//free paths
{
	if (!init_texture_img(data, &data->north, "./sprites/north.xpm"))
		return (false);
	if (!init_texture_img(data, &data->east, "./sprites/east.xpm"))
		return (false);
	if (!init_texture_img(data, &data->south, "./sprites/south.xpm"))
		return (false);
	if (!init_texture_img(data, &data->west, "./sprites/west.xpm"))
		return (false);
	data->frame.img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!data->frame.img)
		return (error("Frame failed initializing"));
	data->frame.addr = mlx_get_data_addr(data->frame.img, &data->frame.bits_per_pixel, 
		&data->frame.line_len, &data->frame.endian);
	if (!data->frame.addr)
		return (error("Frame address failed initializing"));
	return (true);
}

//rename functions of init
bool	init(int ac, char **av, t_data *data)
{
	init_variables(data);
	if (!parser(ac, av, data))
		return (false);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (error("Failed to initialize mlx"));
	data->win_width = 1280;
	data->win_height = 720;
	if (!init_imgs(data))
		return (false);
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "cub3d");
	return (true);
}