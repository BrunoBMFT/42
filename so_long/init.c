/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:34:43 by brfernan          #+#    #+#             */
/*   Updated: 2024/04/10 19:37:26 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	wall_init(t_vars *vars)// ! init with map instead?
{
	vars->map->wall.img = mlx_xpm_file_to_image(vars->mlx, "./assets/edited/wall_north.xpm",
				&vars->map->wall.width, &vars->map->wall.height);
	if (vars->map->wall.img == NULL)
	{
		ft_putendl_fd(INV_WALL, 1);
		exit(1);//change to clean
	}
	vars->map->wall.address = mlx_get_data_addr(vars->map->wall.img,
					&vars->map->wall.bits_per_pixel, &vars->map->wall.line_len,
					&vars->map->wall.endian);
}

void	map_init(t_map *map)
{
	map->map = NULL;
	map->visited = NULL;
}