/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:36:08 by bruno             #+#    #+#             */
/*   Updated: 2024/05/23 00:23:18 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	clean_textures(t_vars *vars)
{
	if (vars->map->wall.img)
		mlx_destroy_image(vars->mlx, vars->map->wall.img);
	if (vars->map->floor.img)
		mlx_destroy_image(vars->mlx, vars->map->floor.img);
	if (vars->map->collectible.img)
		mlx_destroy_image(vars->mlx, vars->map->collectible.img);
	if (vars->map->bomb.img)
		mlx_destroy_image(vars->mlx, vars->map->bomb.img);
	if (vars->map->exit.img)
		mlx_destroy_image(vars->mlx, vars->map->exit.img);
	if (vars->map->death.img)
		mlx_destroy_image(vars->mlx, vars->map->death.img);
}

int	clean(t_vars *vars)
{
	if (vars->player)
		mlx_destroy_image(vars->mlx, vars->player->img.img);
	clean_textures(vars);
	if (vars->load)
		mlx_destroy_image(vars->mlx, vars->load->img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	if (vars->player)
		free(vars->player);
	free(vars->mlx);
	clean_map(vars->map);
	return (0);
}

void	clean_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->map)
	{
		while (map->map[i])
		{
			free(map->map[i]);
			free(map->visited[i++]);
		}
	}
	free(map->map);
	free(map->visited);
	exit(0);
}

void	free_file(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_parser_map(t_map *map)
{
	if (map->map)
		free_file(map->map);
	if (map->visited)
		free_file((char **)map->visited);
}
