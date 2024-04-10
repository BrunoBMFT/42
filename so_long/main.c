/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:50:02 by brfernan          #+#    #+#             */
/*   Updated: 2024/04/10 19:38:15 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	clean(t_map map, t_vars vars, bool *crash)
{
	free_parser(&map);
	if (vars.win)
		mlx_destroy_window(vars.mlx, vars.win);
	if (vars.mlx)
		mlx_destroy_display(vars.mlx);
	if (map.map)
		free_file(map.map);
	if (map.visited)
		free_file((char **)map.visited);
	free(vars.mlx);
	if (crash)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_vars	vars;

	mlx_init(vars);
	map_init(&map);// TODO init vars instead of map and make map already be in vars
	if (!parser(ac, av, &map))
		return(ft_printf("failed successfully"), 1);
	return (ft_printf("e\n"), clean(map, vars, true));
}