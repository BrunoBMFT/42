/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:50:02 by brfernan          #+#    #+#             */
/*   Updated: 2024/04/10 22:49:42 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	clean(t_map *map, t_vars *vars, bool crash)
{
	free_parser(map);
//	if (!vars->win)
//		mlx_destroy_window(vars->mlx, vars->win);
	/*if (vars->mlx)// ! not sure if right
		mlx_destroy_display(vars->mlx);*/
	if (!vars->mlx)
		free(vars->mlx);
//	if (!map->map)
//		free_file(map->map);
//	if (!map->visited)
//		free_file((char **)map->visited);
	if (crash)//no crash
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_vars	vars;

	vars.mlx = mlx_init(vars);//check alloc
	map_init(&map);// TODO init vars instead of map and make map already be in vars
	if (!parser(ac, av, &map))
		return(ft_printf("failed successfully"), 1);
	return (ft_printf("e\n"), clean(&map, &vars, true));
}