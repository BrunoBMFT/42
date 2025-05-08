/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:04:14 by brfernan          #+#    #+#             */
/*   Updated: 2025/05/08 05:57:44 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_variables(t_data *data)
{
	data->file = NULL;
	data->map = NULL;
	data->path_north = NULL;
	data->path_east = NULL;
	data->path_south = NULL;
	data->path_west = NULL;
	data->path_floor = NULL;
	data->path_ceiling = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->north.img = NULL;
	data->east.img = NULL;
	data->south.img = NULL;
	data->west.img = NULL;
	data->frame.img = NULL;
}


bool	init(int ac, char **av, t_data *data)
{
	init_variables(data);
	if (!parser(ac, av, data))
		return (false);
	if (!player_init(data))
		return (false);
	data->door_opened = false;
	data->map_active = true;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (error("Failed to initialize mlx"));
	data->win_width = WIN_WIDTH;
	data->win_height = WIN_HEIGHT;
	if (!init_imgs(data))
		return (false);
	data->win = mlx_new_window(data->mlx,
			data->win_width, data->win_height, "cub3d");
	return (true);
}
