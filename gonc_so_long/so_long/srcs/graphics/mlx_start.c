/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:56:17 by gfontao-          #+#    #+#             */
/*   Updated: 2024/04/12 16:19:31 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

int	mlx_exit(t_data *vars, char *message, int status)
{
	int	ctd;

	ctd = 0;
	while (ctd < 16)
		mlx_destroy_image(vars->mlx, vars->pacman->img[ctd++].img);
	mlx_destroy_image(vars->mlx, vars->load_img->img);
	mlx_destroy_image(vars->mlx, vars->map->wall.img);
	mlx_destroy_image(vars->mlx, vars->map->floor.img);
	mlx_destroy_image(vars->mlx, vars->map->collectible.img);
	mlx_destroy_image(vars->mlx, vars->map->exit.img);
	mlx_destroy_image(vars->mlx, vars->map->border_vertical.img);
	mlx_destroy_image(vars->mlx, vars->map->border_horizontal.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->pacman);
	free(vars->mlx);
	freemap(vars->map, message, status);
	return (0);
}

void	create_all(t_data *vars, t_img *img)
{
	render_map(vars, img);
	render_border(vars, img);
	render_pacman(vars, img);
	put_screen(vars, img);
}

void	mlx_initialize_var(t_data *vars, t_map *map)
{
	int	width;
	int	height;

	vars->map = map;
	vars->width = map->cols * SCALE + BORDER * 2;
	vars->height = map->rows * SCALE + BORDER * 2;
	vars->mlx = mlx_init();
	mlx_get_screen_size(vars->mlx, &width, &height);
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->height, "So_Long");
}

void	mlx_start(t_map *map)
{
	t_data	vars;
	t_img		img;

	mlx_initialize_var(&vars, map);
	initialize_image(&vars, &img, vars.width, vars.height);
	pacman_init(&vars);
	map_init(&vars);
	create_all(&vars, &img);
	mlx_loop_hook(vars.mlx, const_move, &vars);//checks inputs
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win, 17, 1L << 17, mlx_exit, &vars);//x button
	mlx_loop(vars.mlx);//loop
}
