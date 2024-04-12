/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:13:24 by gfontao-          #+#    #+#             */
/*   Updated: 2024/04/12 16:19:31 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	map_init(t_data *vars)
{
	wall_init(vars);
	floor_init(vars);
	exit_init(vars);
	collectible_init(vars);
	border_init(vars);
}

void	render_counter(t_data *vars)
{
	char	*moves;
	int		pos_x;

	pos_x = 25;
	moves = ft_itoa(vars->pacman->moves);
	if (ft_strlen(moves) == 2)
		pos_x -= 5;
	else if (ft_strlen(moves) == 3)
		pos_x -= 10;
	else if (ft_strlen(moves) == 4)
		pos_x -= 15;
	mlx_string_put(vars->mlx, vars->win, pos_x, 30, 0x00FFFFFF, moves);
	free(moves);
}
