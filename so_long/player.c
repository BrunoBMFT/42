/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:03:22 by bruno             #+#    #+#             */
/*   Updated: 2024/04/20 17:41:39 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long.h"

void	render_player(t_vars *vars, t_img *img)
{
    make_img(img, vars->player->img, vars->player->x, vars->player->y);
}

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
	/*vars->packman->dir = 's';
	vars->packman->next = 's';
	vars->packman->prev = 's';
	vars->packman->moves = 0;*/

    vars->player->img.img = mlx_xpm_file_to_image(vars->mlx,
			"./assets/player.xpm", &vars->player->img.width,
			&vars->player->img.height);
	vars->player->img.addr = mlx_get_data_addr(vars->player->img.img,
			&vars->player->img.bits_per_pixel,
			&vars->player->img.line_len,
			&vars->player->img.endian);
    return (true);
}
