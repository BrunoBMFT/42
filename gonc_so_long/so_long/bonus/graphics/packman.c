/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pacman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:36:37 by gfontao-          #+#    #+#             */
/*   Updated: 2024/04/12 16:16:33 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	find_start(t_data *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->map->rows)
	{
		x = 0;
		while (x < vars->map->cols)
		{
			if (vars->map->map[y][x] == 'P')
			{
				vars->pacman->x = x * SCALE + BORDER;
				vars->pacman->y = y * SCALE + BORDER;
				vars->map->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

void	get_addr(t_data *vars)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		vars->pacman->img[i].addr = mlx_get_data_addr(vars->pacman->img[i].img,
				&vars->pacman->img[i].bits_per_pixel,
				&vars->pacman->img[i].line_length,
				&vars->pacman->img[i].endian);
		i++;
	}
}

void	render_pacman(t_data *vars, t_img *img)
{
	static int	i = 0;
	int			direction;

	direction = 0;
	if (vars->pacman->dir == 'r' || vars->pacman->dir == 's')
		direction = 0;
	else if (vars->pacman->dir == 'd')
		direction = 4;
	else if (vars->pacman->dir == 'l')
		direction = 8;
	else if (vars->pacman->dir == 'u')
		direction = 12;
	i = choose_img(vars, img, i, direction);
}

int	choose_img(t_data *vars, t_img *img, int i, int direction)
{
	if (i < 10)
		create_img(img, vars->pacman->img[direction], vars->pacman->x,
			vars->pacman->y);
	else if (i < 20)
		create_img(img, vars->pacman->img[direction + 1], vars->pacman->x,
			vars->pacman->y);
	else if (i < 30)
		create_img(img, vars->pacman->img[direction + 2], vars->pacman->x,
			vars->pacman->y);
	else if (i < 39)
		create_img(img, vars->pacman->img[direction + 3], vars->pacman->x,
			vars->pacman->y);
	else
	{
		create_img(img, vars->pacman->img[direction + 3], vars->pacman->x,
			vars->pacman->y);
		i = -1;
	}
	i++;
	return (i);
}
