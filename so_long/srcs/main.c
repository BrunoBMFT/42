/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:18:28 by bruno             #+#    #+#             */
/*   Updated: 2024/04/25 17:00:05 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
// ! map validates even if player is trapped
// TODO find_start doesnt need to exist, it already exists in the parser
// TODO change mas.has_exit and rest to ints (so floodfill can do the count)
// TODO make multiple collectible
// TODO check_char maybe not needed, since floodfill with find how many players there are
// TODO might not need find start
// remove exit from the check moves?
// * instead of vars timer, use time library?
// * if multiple bombs, only the one touched by player needs to dissappear
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
