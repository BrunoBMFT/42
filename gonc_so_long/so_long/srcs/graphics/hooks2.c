/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:42:37 by gfontao-          #+#    #+#             */
/*   Updated: 2024/04/12 16:19:08 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	check_collectables(t_data *vars)
{
	int	x;
	int	y;

	x = (vars->pacman->x - BORDER) / SCALE;
	y = (vars->pacman->y - BORDER) / SCALE;
	if ((vars->pacman->y - BORDER) % SCALE != 0 || (vars->pacman->x - BORDER)
		% SCALE != 0)
		return ;
	if (vars->map->map[y][x] == 'C')
	{
		vars->map->map[y][x] = '0';
		vars->map->collectibles_count--;
	}
	if (vars->map->collectibles_count == 0 && vars->map->map[y][x] == 'E')
	{
		ft_printf("You win!\n");
		mlx_exit(vars, NULL, 0);
	}
}

int	key_hook(int keycode, t_data *vars)
{
	vars->pacman->prev = vars->pacman->dir;
	if (keycode == 65307)
		mlx_exit(vars, NULL, 0);
	if (keycode == 'a')
		vars->pacman->next = 'l';
	if (keycode == 'd')
		vars->pacman->next = 'r';
	if (keycode == 'w')
		vars->pacman->next = 'u';
	if (keycode == 's')
		vars->pacman->next = 'd';
	return (0);
}

int	const_move(t_data *vars)
{
	int	flag;

	flag = FALSE;
	if (vars->pacman->next == 'l')
		flag = move_pacman(vars, 'a', 0);
	else if (vars->pacman->next == 'r')
		flag = move_pacman(vars, 'd', 0);
	else if (vars->pacman->next == 'u')
		flag = move_pacman(vars, 'w', 0);
	else if (vars->pacman->next == 'd')
		flag = move_pacman(vars, 's', 0);
	if (flag == TRUE)
		return (0);
	if (vars->pacman->dir == 'l')
		flag = move_pacman(vars, 'a', 1);
	else if (vars->pacman->dir == 'r')
		flag = move_pacman(vars, 'd', 1);
	else if (vars->pacman->dir == 'u')
		flag = move_pacman(vars, 'w', 1);
	else if (vars->pacman->dir == 'd')
		flag = move_pacman(vars, 's', 1);
	return (0);
}
