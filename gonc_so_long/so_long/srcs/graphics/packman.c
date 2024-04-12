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
	vars->pacman->img[0].addr = mlx_get_data_addr(vars->pacman->img[0].img,
			&vars->pacman->img[0].bits_per_pixel,
			&vars->pacman->img[0].line_length,
			&vars->pacman->img[0].endian);
}

void	render_pacman(t_data *vars, t_img *img)
{
	create_img(img, vars->pacman->img[0], vars->pacman->x, vars->pacman->y);
}
