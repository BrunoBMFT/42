/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:58:59 by bruno             #+#    #+#             */
/*   Updated: 2024/04/19 20:53:32 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long.h"

void	wall_init(t_vars *vars)
{
	vars->map->wall.img = mlx_xpm_file_to_image(vars->mlx,
			"./assets/wall.xpm", &vars->map->wall.width,
			&vars->map->wall.height);
	if (vars->map->wall.img == NULL)
		ft_putendl(INV_WALL);
	vars->map->wall.addr = mlx_get_data_addr(vars->map->wall.img,
			&vars->map->wall.bits_per_pixel, &vars->map->wall.line_len,
			&vars->map->wall.endian);
}

void	floor_init(t_vars *vars)
{
	vars->map->floor.img = mlx_xpm_file_to_image(vars->mlx,
			"./assets/floor.xpm", &vars->map->floor.width,
			&vars->map->floor.height);
	if (vars->map->floor.img == NULL)
		ft_putendl(INV_FLOOR);
	vars->map->floor.addr = mlx_get_data_addr(vars->map->floor.img,
			&vars->map->floor.bits_per_pixel, &vars->map->floor.line_len,
			&vars->map->floor.endian);
}

/*
void	wall_north_init(t_vars *vars)
{
	vars->map->wall_north.img = mlx_xpm_file_to_image(vars->mlx,
			"./assets/wall_north.xpm", &vars->map->wall_north.width,
			&vars->map->wall_north.height);
	if (vars->map->wall_north.img == NULL)
		ft_putendl(INV_WALL_N);
	vars->map->wall_north.addr = mlx_get_data_addr(vars->map->wall_north.img,
			&vars->map->wall_north.bits_per_pixel, &vars->map->wall_north.line_len,
			&vars->map->wall_north.endian);
}

void	wall_north_east_init(t_vars *vars)
{
	vars->map->wall_north_east.img = mlx_xpm_file_to_image(vars->mlx,
			"./assets/wall_north_east.xpm", &vars->map->wall_north_east.width,
			&vars->map->wall_north_east.height);
	if (vars->map->wall_north_east.img == NULL)
		ft_putendl(INV_WALL_NE);
	vars->map->wall_north_east.addr = mlx_get_data_addr(vars->map->wall_north_east.img,
			&vars->map->wall_north_east.bits_per_pixel, &vars->map->wall_north_east.line_len,
			&vars->map->wall_north_east.endian);
}

void	wall_east_init(t_vars *vars)
{
	vars->map->wall_east.img = mlx_xpm_file_to_image(vars->mlx,
			"./assets/wall_east.xpm", &vars->map->wall_east.width,
			&vars->map->wall_east.height);
	if (vars->map->wall_east.img == NULL)
		ft_putendl(INV_WALL_E);
	vars->map->wall_east.addr = mlx_get_data_addr(vars->map->wall_east.img,
			&vars->map->wall_east.bits_per_pixel, &vars->map->wall_east.line_len,
			&vars->map->wall_east.endian);
}

void	wall_north_west_init(t_vars *vars)
{
	vars->map->wall_north_west.img = mlx_xpm_file_to_image(vars->mlx,
			"./assets/wall_north_west.xpm", &vars->map->wall_north_west.width,
			&vars->map->wall_north_west.height);
	if (vars->map->wall_north_west.img == NULL)
		ft_putendl(INV_WALL_NW);
	vars->map->wall_north_west.addr = mlx_get_data_addr(vars->map->wall_north_west.img,
			&vars->map->wall_north_west.bits_per_pixel, &vars->map->wall_north_west.line_len,
			&vars->map->wall_north_west.endian);
}

void	wall_west_init(t_vars *vars)
{
	vars->map->wall_west.img = mlx_xpm_file_to_image(vars->mlx,
			"./assets/wall_west.xpm", &vars->map->wall_west.width,
			&vars->map->wall_west.height);
	if (vars->map->wall_west.img == NULL)
		ft_putendl(INV_WALL_W);
	vars->map->wall_west.addr = mlx_get_data_addr(vars->map->wall_west.img,
			&vars->map->wall_west.bits_per_pixel, &vars->map->wall_west.line_len,
			&vars->map->wall_west.endian);
}

void	wall_CENTER_init(t_vars *vars)
{
	vars->map->wall.img = mlx_xpm_file_to_image(vars->mlx,
			"./assets/CENTER.xpm", &vars->map->wall.width,
			&vars->map->wall.height);
	if (vars->map->wall.img == NULL)
		ft_putendl(INV_WALL);
	vars->map->wall.addr = mlx_get_data_addr(vars->map->wall.img,
			&vars->map->wall.bits_per_pixel, &vars->map->wall.line_len,
			&vars->map->wall.endian);
}*/