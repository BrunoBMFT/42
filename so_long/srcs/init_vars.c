/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:50:36 by bruno             #+#    #+#             */
/*   Updated: 2024/04/22 00:07:20 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	find_start(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->map->row)
	{
		x = 0;
		while (x < vars->map->col)
		{
			if (vars->map->map[y][x] == 'P')
			{
				vars->player->x = x * SCALE;
				vars->player->y = y * SCALE;
				vars->map->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

bool	player_init(t_vars *vars)
{
	vars->player = malloc(sizeof(t_player));
	if (!vars->player)
		return (ft_putendl(ERR_ALLOC_PLAYER), false);
	find_start(vars);
	vars->player->dir = 'N';
	vars->player->moves = 1;
	vars->player->can_exit = false;
	vars->player->img.img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/assets/player.xpm", &vars->player->img.width,
			&vars->player->img.height);
	if (!vars->player->img.img)
		return (ft_putendl(INV_PLAYER), false);
	vars->player->img.addr = mlx_get_data_addr(vars->player->img.img,
			&vars->player->img.bits_per_pixel,
			&vars->player->img.line_len,
			&vars->player->img.endian);
	return (true);
}

bool	mlx_init_vars(t_vars *vars, t_map *map)
{
	int	width;
	int	height;

	vars->map = map;
	vars->width = map->col * SCALE;
	vars->height = map->row * SCALE;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (ft_putendl(ERR_MLX), false);
	mlx_get_screen_size(vars->mlx, &width, &height);
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->height, "so_long");
	if (!vars->win)
		return (ft_putendl(ERR_WIN), false);
	return (true);
}

bool	init_img(t_vars *vars, t_img *img, int width, int height)
{
	img->img = mlx_new_image(vars->mlx, width, height);
	if (!img->img)
		return (ft_putendl(ERR_IMG), false);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	vars->load = img;
	return (true);
}
