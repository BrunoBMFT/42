/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:34:50 by bruno             #+#    #+#             */
/*   Updated: 2024/04/20 19:00:15 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long.h"

int	handle_move(t_vars *vars)
{
	if (vars->player->input == 'N')
		vars->player->y -= 1;
	if (vars->player->input == 'E')
		vars->player->x += 1;
	if (vars->player->input == 'S')
		vars->player->y += 1;
	if (vars->player->input == 'W')
		vars->player->x -= 1;
	render(vars, vars->load);
}

int	handle_input(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape)
		clean(vars);
	if (keysym == 'w' || keysym == XK_Up)
	{
		vars->player->input = 'N';
		ft_putendl("move up");
	}
	if (keysym == 'd' || keysym == XK_Right)
	{
		vars->player->input = 'E';
		ft_putendl("move right");
	}
	if (keysym == 's' || keysym == XK_Down)
	{
		vars->player->input = 'S';
		ft_putendl("move down");
	}
	if (keysym == 'a' || keysym == XK_Left)
	{
		vars->player->input = 'W';
		ft_putendl("move left");
	}
	return (0);
}
