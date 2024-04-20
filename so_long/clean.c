/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:36:08 by bruno             #+#    #+#             */
/*   Updated: 2024/04/20 16:36:16 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long.h"

void	freemap(t_map *map)//make my own
{
	int	ctd;

	ctd = 0;
	while (map->map[ctd])
		free(map->map[ctd++]);
	free(map->map);
	exit(0);
}

int	clean(t_vars *vars)//make my own
{
//	int	ctd = 0;
//	while (ctd < 16)
//		mlx_destroy_image(vars->mlx, vars->packman->img[ctd++].img);
//	mlx_destroy_image(vars->mlx, vars->load_img->img);
	if (vars->map)
		mlx_destroy_image(vars->mlx, vars->map->wall.img);
//	mlx_destroy_image(vars->mlx, vars->map->floor.img);
//	mlx_destroy_image(vars->mlx, vars->map->collectible.img);
//	mlx_destroy_image(vars->mlx, vars->map->exit.img);
//	mlx_destroy_image(vars->mlx, vars->map->border_vertical.img);
//	mlx_destroy_image(vars->mlx, vars->map->border_horizontal.img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
//	free(vars->packman);
	free(vars->mlx);
	freemap(vars->map);
	return (0);
}