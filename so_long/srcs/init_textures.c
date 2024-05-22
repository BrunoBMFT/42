/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:58:59 by bruno             #+#    #+#             */
/*   Updated: 2024/05/23 00:43:06 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

bool	map_init(t_vars *vars)
{
	int	ret;

	ret = 0;
	if (!wall_init(vars))
		ret = 1;
	if (!floor_init(vars))
		ret = 1;
	if (!collectible_init(vars))
		ret = 1;
	if (!exit_init(vars))
		ret = 1;
	if (!bomb_init(vars))
		ret = 1;
	if (!death_init(vars))
		ret = 1;
	if (ret == 1)
		return (false);
	return (true);
}

bool	wall_init(t_vars *vars)
{
	if (!access("./includes/assets/wall.xpm", F_OK))
	{
		vars->map->wall.img = mlx_xpm_file_to_image(vars->mlx,
				"./includes/assets/wall.xpm", &vars->map->wall.width,
				&vars->map->wall.height);
		if (!vars->map->wall.img)
			return (ft_putendl(INV_WALL), false);
		vars->map->wall.addr = mlx_get_data_addr(vars->map->wall.img,
				&vars->map->wall.bits_per_pixel, &vars->map->wall.line_len,
				&vars->map->wall.endian);
		return (true);
	}
	vars->map->wall.img = NULL;
	return (ft_putendl(INV_WALL), false);
}

bool	floor_init(t_vars *vars)
{
	if (!access("./includes/assets/floor.xpm", F_OK))
	{
		vars->map->floor.img = mlx_xpm_file_to_image(vars->mlx,
				"./includes/assets/floor.xpm", &vars->map->floor.width,
				&vars->map->floor.height);
		if (!vars->map->floor.img)
			return (ft_putendl(INV_FLOOR), false);
		vars->map->floor.addr = mlx_get_data_addr(vars->map->floor.img,
				&vars->map->floor.bits_per_pixel, &vars->map->floor.line_len,
				&vars->map->floor.endian);
		return (true);
	}
	vars->map->floor.img = NULL;
	return (ft_putendl(INV_FLOOR), false);
}

bool	collectible_init(t_vars *vars)
{
	if (!access("./includes/assets/collectible.xpm", F_OK))
	{
		vars->map->collectible.img = mlx_xpm_file_to_image(vars->mlx,
				"./includes/assets/collectible.xpm",
				&vars->map->collectible.width,
				&vars->map->collectible.height);
		if (!vars->map->collectible.img)
			return (ft_putendl(INV_COLLECTIBLE), false);
		vars->map->collectible.addr = mlx_get_data_addr(
				vars->map->collectible.img,
				&vars->map->collectible.bits_per_pixel,
				&vars->map->collectible.line_len,
				&vars->map->collectible.endian);
		return (true);
	}
	vars->map->collectible.img = NULL;
	return (ft_putendl(INV_COLLECTIBLE), false);
}

bool	bomb_init(t_vars *vars)
{
	if (!access("./includes/assets/bomb.xpm", F_OK))
	{
		vars->map->bomb.img = mlx_xpm_file_to_image(vars->mlx,
				"./includes/assets/bomb.xpm", &vars->map->bomb.width,
				&vars->map->bomb.height);
		if (!vars->map->bomb.img)
			return (ft_putendl(INV_BOMB), false);
		vars->map->bomb.addr = mlx_get_data_addr(vars->map->bomb.img,
				&vars->map->bomb.bits_per_pixel, &vars->map->bomb.line_len,
				&vars->map->bomb.endian);
		return (true);
	}
	vars->map->bomb.img = NULL;
	return (ft_putendl(INV_BOMB), false);
}
