/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:18:28 by bruno             #+#    #+#             */
/*   Updated: 2024/04/26 00:33:36 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
// TODO make multiple collectible
// TODO might not need find start
// remove exit from the check moves?
int	main(int ac, char **av)
{
	t_map	map;
	t_vars	vars;
	t_img	img;
	
	if (!parser(ac, av, &map))
		return (1);
	if (!mlx_init_vars(&vars, &map))
		return (clean(&vars), 1);
	if (!init_img(&vars, &img, vars.width, vars.height))
		return (clean(&vars), 1);
	if (!player_init(&vars))
		return (clean(&vars), 1);
	if (!map_init(&vars))
		return (clean(&vars), 1);
	render(&vars, &img);
	mlx_loop_hook(vars.mlx, handle_move, &vars);
	mlx_key_hook(vars.win, handle_input, &vars);
	mlx_hook(vars.win, 17, 1L << 17, clean, &vars);
	mlx_loop(vars.mlx);
}
