/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:46:44 by gfontao-          #+#    #+#             */
/*   Updated: 2024/04/12 16:19:31 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	render_map(t_data *vars, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (vars->map->map[y])
	{
		x = 0;
		while (vars->map->map[y][x])
		{
			render_map_condition(vars, img, x, y);
			x++;
		}
		y++;
	}
}

void	render_map_condition(t_data *vars, t_img *img, int x, int y)
{
	if (vars->map->map[y][x] == '1')
	{
		create_img(img, vars->map->wall, (x * SCALE) + BORDER, (y * SCALE)
			+ BORDER);
	}
	else if (vars->map->map[y][x] == '0')
		create_img(img, vars->map->floor, (x * SCALE) + BORDER, (y * SCALE)
			+ BORDER);
	else if (vars->map->map[y][x] == 'C')
		create_img(img, vars->map->collectible, (x * SCALE) + BORDER, (y * SCALE)
			+ BORDER);
	else if (vars->map->map[y][x] == 'E' && vars->map->collectibles_count == 0)
		create_img(img, vars->map->exit, (x * SCALE) + BORDER, (y * SCALE)
			+ BORDER);
	else if (vars->map->map[y][x] == 'E')
		create_img(img, vars->map->floor, (x * SCALE) + BORDER, (y * SCALE)
			+ BORDER);
}

void	render_border(t_data *vars, t_img *img)
{
	int	x;
	int	y;

	(void)img;
	y = 0;
	while (y < vars->map->rows)
	{
		x = 0;
		while (x < vars->map->cols)
		{
			// if (vars->map->map[y][x] == '1')
			// 	create_border(vars, img, x, y);
			x++;
		}
		y++;
	}
}

void	create_border(t_data *vars, t_img *img, int x, int y)
{
	if (x + 1 < vars->map->cols && vars->map->map[y][x + 1] == '1')
	{
		if (y + 1 < vars->map->rows && vars->map->map[y + 1][x] == '1'
			&& vars->map->map[y + 1][x + 1] == '1')
			pixel_fix(img, x, y);
		create_img(img, vars->map->border_vertical, ((x + 1) * SCALE) + BORDER
			- 1, (y * SCALE) + BORDER + 1);
	}
	if (x - 1 >= 0 && vars->map->map[y][x - 1] == '1')
		create_img(img, vars->map->border_vertical, (x * SCALE) + BORDER, (y
				* SCALE) + BORDER + 1);
	if (y + 1 < vars->map->rows && vars->map->map[y + 1][x] == '1')
		create_img(img, vars->map->border_horizontal, (x * SCALE) + BORDER + 1,
			((y + 1) * SCALE) + BORDER - 1);
	if (y - 1 >= 0 && vars->map->map[y - 1][x] == '1')
		create_img(img, vars->map->border_horizontal, (x * SCALE) + BORDER + 1,
			(y * SCALE) + BORDER);
}

void	pixel_fix(t_img *img, int x, int y)
{
	put_pixel(img, ((x + 1) * SCALE) + BORDER - 1, ((y + 1) * SCALE) + BORDER
		- 1, WALL_COLOR);
	put_pixel(img, ((x + 1) * SCALE) + BORDER, ((y + 1) * SCALE) + BORDER - 1,
		WALL_COLOR);
	put_pixel(img, ((x + 1) * SCALE) + BORDER - 1, ((y + 1) * SCALE) + BORDER,
		WALL_COLOR);
	put_pixel(img, ((x + 1) * SCALE) + BORDER, ((y + 1) * SCALE) + BORDER,
		WALL_COLOR);
}
