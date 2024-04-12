/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:54:58 by gfontao-          #+#    #+#             */
/*   Updated: 2024/04/12 16:19:08 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

t_bool	move_pacman(t_data *vars, char direction, int status)
{
	int	x;
	int	y;

	x = vars->pacman->x;
	y = vars->pacman->y;
	if (direction == 'a' && vars->map->map[(vars->pacman->y - BORDER)
			/ SCALE][(vars->pacman->x - MOVE_SPEED - BORDER) / SCALE] != '1')
		if (((vars->pacman->y - BORDER) % SCALE) == 0
			|| vars->map->map[(vars->pacman->y - BORDER) / SCALE
				+ 1][(vars->pacman->x - MOVE_SPEED - BORDER) / SCALE] != '1')
			vars->pacman->x -= MOVE_SPEED;
	if (direction == 'd' && vars->map->map[(vars->pacman->y - BORDER)
			/ SCALE][(vars->pacman->x - BORDER) / SCALE + 1] != '1')
		if (((vars->pacman->y - BORDER) % SCALE) == 0
			|| vars->map->map[(vars->pacman->y - BORDER) / SCALE
				+ 1][(vars->pacman->x - BORDER) / SCALE + 1] != '1')
			vars->pacman->x += MOVE_SPEED;
	vertical_move(vars, direction);
	return (check_map_state(vars, status, x, y));
}

void	vertical_move(t_data *vars, char direction)
{
	if (direction == 'w' && vars->map->map[(vars->pacman->y - MOVE_SPEED
				- BORDER) / SCALE][(vars->pacman->x - BORDER) / SCALE] != '1')
		if (((vars->pacman->x - BORDER) % SCALE) == 0
			|| vars->map->map[(vars->pacman->y - MOVE_SPEED - BORDER)
				/ SCALE][(vars->pacman->x - BORDER) / SCALE + 1] != '1')
			vars->pacman->y -= MOVE_SPEED;
	if (direction == 's' && vars->map->map[(vars->pacman->y - BORDER) / SCALE
			+ 1][(vars->pacman->x - BORDER) / SCALE] != '1')
		if (((vars->pacman->x - BORDER) % SCALE) == 0
			|| vars->map->map[(vars->pacman->y - BORDER) / SCALE
				+ 1][(vars->pacman->x - BORDER) / SCALE + 1] != '1')
			vars->pacman->y += MOVE_SPEED;
}

t_bool	check_map_state(t_data *vars, int status, int x, int y)
{
	t_bool				flag;
	static long long	last_time = 0;

	flag = FALSE;
	if (x != vars->pacman->x || y != vars->pacman->y)
	{
		if (status == 0 && vars->pacman->dir != vars->pacman->next)
			vars->pacman->moves++;
		if (status == 0)
			vars->pacman->dir = vars->pacman->next;
		vars->pacman->prev = vars->pacman->dir;
		check_collectables(vars);
		while (check_time(&last_time) == FALSE)
			;
		create_all(vars, vars->load_img);
		flag = TRUE;
	}
	else
		vars->pacman->dir = vars->pacman->prev;
	return (flag);
}

t_bool	check_time(long long *last_time)
{
	struct timeval	tv;
	long long		current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000000 + tv.tv_usec;
	if (current_time - *last_time >= FRAME_TIME)
	{
		*last_time = current_time;
		return (TRUE);
	}
	else
		return (FALSE);
}
