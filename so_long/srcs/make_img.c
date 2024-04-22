/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:41:39 by bruno             #+#    #+#             */
/*   Updated: 2024/04/22 00:08:28 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*offset;

	offset = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}

void	make_img(t_img *img, t_img src, int x, int y)
{
	int				i;
	int				j;
	unsigned int	color;

	i = 0;
	while (i < src.width)
	{
		j = 0;
		while (j < src.height)
		{
			color = get_pixel(&src, i, j);
			put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	render_map_textures(t_vars *vars, t_img *img, int x, int y)
{
	if (vars->map->map[y][x] == '1')
		make_img(img, vars->map->wall, (x * SCALE), (y * SCALE));
	if (vars->map->map[y][x] == '0'
		|| (vars->map->map[y][x] == 'E' && !vars->player->can_exit)
		|| (vars->map->map[y][x] == 'C' && vars->player->can_exit))
		make_img(img, vars->map->floor, (x * SCALE), (y * SCALE));
	if (vars->map->map[y][x] == 'C' && !vars->player->can_exit)
		make_img(img, vars->map->collectible, (x * SCALE), (y * SCALE));
	if (vars->map->map[y][x] == 'E' && vars->player->can_exit)
		make_img(img, vars->map->exit, (x * SCALE), (y * SCALE));
}

void	render_map(t_vars *vars, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (vars->map->map[y])
	{
		x = 0;
		while (vars->map->map[y][x])
		{
			render_map_textures(vars, img, x, y);
			x++;
		}
		y++;
	}
}
