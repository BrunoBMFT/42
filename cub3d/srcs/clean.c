/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:36:01 by bruno             #+#    #+#             */
/*   Updated: 2025/03/18 17:21:34 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clean_texture_path(t_data *data)//have this run after img is saved
{
	if (data->p_north)
		free(data->p_north);
	if (data->p_east)
		free(data->p_east);
	if (data->p_south)
		free(data->p_south);
	if (data->p_west)
		free(data->p_west);
	if (data->c_floor)
		free(data->c_floor);
	if (data->c_ceiling)
		free(data->c_ceiling);
}

void	clean_imgs(t_data *data)
{
	//test img clean
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
	clean_imgs(data);//ugly
	if (data->frame.img)
		mlx_destroy_image(data->mlx, data->frame.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx){
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	clean_texture_path(data);
	return (0);
}
