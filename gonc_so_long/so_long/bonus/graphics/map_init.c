/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:36:51 by gfontao-          #+#    #+#             */
/*   Updated: 2024/04/12 16:19:31 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	wall_init(t_data *vars)
{
	vars->map->wall.img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/wall.xpm", &vars->map->wall.width,
			&vars->map->wall.height);
	if (vars->map->wall.img == NULL)
		error_message("Error\nInvalid wall texture\n");
	vars->map->wall.addr = mlx_get_data_addr(vars->map->wall.img,
			&vars->map->wall.bits_per_pixel, &vars->map->wall.line_length,
			&vars->map->wall.endian);
}

void	floor_init(t_data *vars)
{
	vars->map->floor.img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/floor.xpm", &vars->map->floor.width,
			&vars->map->floor.height);
	if (vars->map->floor.img == NULL)
		error_message("Error\nInvalid floor texture\n");
	vars->map->floor.addr = mlx_get_data_addr(vars->map->floor.img,
			&vars->map->floor.bits_per_pixel, &vars->map->floor.line_length,
			&vars->map->floor.endian);
}

void	exit_init(t_data *vars)
{
	vars->map->exit.img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/exit.xpm", &vars->map->exit.width,
			&vars->map->exit.height);
	if (vars->map->exit.img == NULL)
		error_message("Error\nInvalid exit texture\n");
	vars->map->exit.addr = mlx_get_data_addr(vars->map->exit.img,
			&vars->map->exit.bits_per_pixel, &vars->map->exit.line_length,
			&vars->map->exit.endian);
}

void	collectible_init(t_data *vars)
{
	vars->map->collectible.img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/collectible.xpm", &vars->map->collectible.width,
			&vars->map->collectible.height);
	if (vars->map->collectible.img == NULL)
		error_message("Error\nInvalid collectible texture\n");
	vars->map->collectible.addr = mlx_get_data_addr(vars->map->collectible.img,
			&vars->map->collectible.bits_per_pixel,
			&vars->map->collectible.line_length, &vars->map->collectible.endian);
}

void	border_init(t_data *vars)
{
	vars->map->border_vertical.img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/border_vertical.xpm",
			&vars->map->border_vertical.width,
			&vars->map->border_vertical.height);
	if (vars->map->border_vertical.img == NULL)
		error_message("Error\nInvalid border texture\n");
	vars->map->border_vertical.addr = mlx_get_data_addr
		(vars->map->border_vertical.img,
			&vars->map->border_vertical.bits_per_pixel,
			&vars->map->border_vertical.line_length,
			&vars->map->border_vertical.endian);
	vars->map->border_horizontal.img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/border_horizontal.xpm",
			&vars->map->border_horizontal.width,
			&vars->map->border_horizontal.height);
	if (vars->map->border_horizontal.img == NULL)
		error_message("Error\nInvalid border texture\n");
	vars->map->border_horizontal.addr = mlx_get_data_addr
		(vars->map->border_horizontal.img,
			&vars->map->border_horizontal.bits_per_pixel,
			&vars->map->border_horizontal.line_length,
			&vars->map->border_horizontal.endian);
}
