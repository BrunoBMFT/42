/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:50:02 by brfernan          #+#    #+#             */
/*   Updated: 2024/04/12 16:10:12 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean(t_map map, t_vars vars)
{
	ft_putstr("eee");
	free_parser(&map);
	if (vars.win)
		mlx_destroy_display(vars.mlx);
//	if (vars.mlx)
//		mlx_destroy_display(vars.mlx);
	if (map.map)
		free_file(map.map);
	if (map.visited)
		free_file((char **)map.visited);
	free(vars.mlx);
}

bool	mlx_init_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (ft_putendl("he"), false);
	return (true);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_vars	vars;

	if (!parser(ac, av, &map))
		return(ft_printf("failed successfully"), 1);
	map_init(&map, &vars);// TODO init vars instead of map and make map already be in vars
	if (!mlx_init_vars(&vars))
		return (clean(map, vars), 1);

	vars.win = mlx_new_window(vars.mlx, 600, 600, "so_long");
	if (!vars.win)
		return (clean(map, vars), 1);

	mlx_key_hook(vars.win, handle_input, &vars);

	mlx_loop(vars.mlx);

	return (ft_printf("ran\n"), clean(map, vars), 0);
}