/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:53:55 by bruno             #+#    #+#             */
/*   Updated: 2024/12/20 11:07:43 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_north(t_data *data)
{
	data->texture->north = malloc(sizeof(t_img));
	if (!data->texture->north)
		error(data, "Error allocating memory for north");
	data->texture->north->img = mlx_xpm_file_to_image(data->mlx, data->p_north,
			&data->texture->north->width, &data->texture->north->height);
	if (!data->texture->north->img)
		error(data, "North image failed to open");
	data->texture->north->addr = mlx_get_data_addr(data->texture->north->img,
			&data->texture->north->bits_per_pixel,
			&data->texture->north->line_len, &data->texture->north->endian);
}

void	init_east(t_data *data)
{
	data->texture->east = malloc(sizeof(t_img));
	if (!data->texture->east)
		error(data, "Error allocating memory for east");
	data->texture->east->img = mlx_xpm_file_to_image(data->mlx, data->p_east,
			&data->texture->east->width, &data->texture->east->height);
	if (!data->texture->east->img)
		error(data, "East image failed to open");
	data->texture->east->addr = mlx_get_data_addr(data->texture->east->img,
			&data->texture->east->bits_per_pixel,
			&data->texture->east->line_len, &data->texture->east->endian);
}

void	init_south(t_data *data)
{
	data->texture->south = malloc(sizeof(t_img));
	if (!data->texture->south)
		error(data, "Error allocating memory for south");
	data->texture->south->img = mlx_xpm_file_to_image(data->mlx, data->p_south,
			&data->texture->south->width, &data->texture->south->height);
	if (!data->texture->south->img)
		error(data, "South image failed to open");
	data->texture->south->addr = mlx_get_data_addr(data->texture->south->img,
			&data->texture->south->bits_per_pixel,
			&data->texture->south->line_len, &data->texture->south->endian);
}

void	init_west(t_data *data)
{
	data->texture->west = malloc(sizeof(t_img));
	if (!data->texture->west)
		error(data, "Error allocating memory for west");
	data->texture->west->img = mlx_xpm_file_to_image(data->mlx, data->p_west,
			&data->texture->west->width, &data->texture->west->height);
	if (!data->texture->west->img)
		error(data, "West image failed to open");
	data->texture->west->addr = mlx_get_data_addr(data->texture->west->img,
			&data->texture->west->bits_per_pixel,
			&data->texture->west->line_len, &data->texture->west->endian);
}

void	init_textures(t_data *data)
{
	data->texture = malloc(sizeof(t_img) * 4);
	if (!data->texture)
		error(data, "Error allocating memory for textures");
	data->texture->north = NULL;
	data->texture->east = NULL;
	data->texture->south = NULL;
	data->texture->west = NULL;
	init_north(data);
	init_east(data);
	init_south(data);
	init_west(data);
}
