/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:36:01 by bruno             #+#    #+#             */
/*   Updated: 2025/04/07 04:56:29 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clean_texture_path(t_data *data)
{
	if (data->path_north)
		free(data->path_north);
	if (data->path_east)
		free(data->path_east);
	if (data->path_south)
		free(data->path_south);
	if (data->path_west)
		free(data->path_west);
	if (data->path_floor)
		free(data->path_floor);
	if (data->path_ceiling)
		free(data->path_ceiling);
}

void	clean_imgs(t_data *data)
{
	if (data->north.img)
		mlx_destroy_image(data->mlx, data->north.img);
	if (data->east.img)
		mlx_destroy_image(data->mlx, data->east.img);
	if (data->south.img)
		mlx_destroy_image(data->mlx, data->south.img);
	if (data->west.img)
		mlx_destroy_image(data->mlx, data->west.img);
}

int	clean_everything(t_data *data)
{
	if (!data)
		return (0);
	if (data->file)
		free_array(data->file);
	if (data->map)
		free_array(data->map);
	clean_imgs(data);
	if (data->frame.img)
		mlx_destroy_image(data->mlx, data->frame.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	clean_texture_path(data);
	return (0);
}

int	clean_exit(t_data *data)
{
	clean_everything(data);
	exit(0);
	return (0);
}
