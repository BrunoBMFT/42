/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:41:39 by bruno             #+#    #+#             */
/*   Updated: 2024/05/24 19:48:01 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render(t_vars *vars, t_img *img)
{
	render_map(vars, img);
	render_player(vars, img);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
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

void	render_map_textures(t_vars *vars, t_img *img, int x, int y)
{
	if (vars->map->map[y][x] == '1')
		make_img(img, vars->map->wall, (x * SCALE), (y * SCALE));
	if (vars->map->map[y][x] == '0'
		|| (vars->map->map[y][x] == 'E' && !vars->player->can_exit))
		make_img(img, vars->map->floor, (x * SCALE), (y * SCALE));
	if (vars->map->map[y][x] == 'C' && !vars->player->can_exit)
		make_img(img, vars->map->collectible, (x * SCALE), (y * SCALE));
	if (vars->map->map[y][x] == 'B')
		make_img(img, vars->map->bomb, (x * SCALE), (y * SCALE));
	if (vars->map->map[y][x] == 'E' && vars->player->can_exit)
		make_img(img, vars->map->exit, (x * SCALE), (y * SCALE));
}

void	render_player(t_vars *vars, t_img *img)
{
	if (vars->player->is_alive)
		make_img(img, vars->player->img, vars->player->x, vars->player->y);
}
