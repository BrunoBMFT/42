/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:34:50 by bruno             #+#    #+#             */
/*   Updated: 2024/04/21 17:14:02 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long.h"

int	handle_move(t_vars *vars)//might not need?
{
	render(vars, vars->load);
}

void	check_moves(t_vars *vars, int x, int y)
{
	if (vars->player->x != x || vars->player->y != y)
		ft_printf("%d\n", vars->player->moves++);
}

void	move_player(t_vars *vars)
{
	int	x = vars->player->x;
	int	y = vars->player->y;
	if (vars->player->input == 'N' && vars->map->map[vars->player->y / SCALE - 1][vars->player->x / SCALE] != '1')//might be wrong (low lft corner)
		vars->player->y -= 1 * SCALE;
	if (vars->player->input == 'S' && vars->map->map[vars->player->y / SCALE + 1][vars->player->x / SCALE] != '1')
		vars->player->y += 1 * SCALE;
	if (vars->player->input == 'E' && vars->map->map[vars->player->y / SCALE][vars->player->x / SCALE + 1] != '1')
		vars->player->x += 1 * SCALE;
	if (vars->player->input == 'W' && vars->map->map[vars->player->y / SCALE][vars->player->x / SCALE - 1] != '1')
		vars->player->x -= 1 * SCALE;
	check_moves(vars, x, y);
}

int	handle_input(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape)
		clean(vars);
	if (keysym == 'w' || keysym == XK_Up)
		vars->player->input = 'N';
	if (keysym == 'd' || keysym == XK_Right)
		vars->player->input = 'E';
	if (keysym == 's' || keysym == XK_Down)
		vars->player->input = 'S';
	if (keysym == 'a' || keysym == XK_Left)
		vars->player->input = 'W';
	move_player(vars);
	return (0);
}