/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:18:28 by bruno             #+#    #+#             */
/*   Updated: 2024/04/21 18:34:47 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long.h"
// ! turn every function to bool
// ! image flickering
// TODO use putendl + defined string
// TODO Collectible
// remove exit from the check
void	mlx_init_vars(t_vars *vars, t_map *map)
{
	int	width;
	int	height;

	vars->map = map;//map is checked before
	vars->width = map->col * SCALE;
	vars->height = map->row * SCALE;
	vars->mlx = mlx_init();
	mlx_get_screen_size(vars->mlx, &width, &height);//check if works with fixed values
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->height, "so_long");//check if works with fixed values
	if (!vars->win)
		ft_putstr("new window failed");
}

void	init_img(t_vars *vars, t_img *img, int width, int height)
{
	img->img = mlx_new_image(vars->mlx, width, height);
	if (!img->img)
		ft_putstr("new image failed");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	vars->load = img;
}

void	map_init(t_vars *vars)
{
	wall_init(vars);
	floor_init(vars);
	collectible_init(vars);
	exit_init(vars);
}

void	render_map_textures(t_vars *vars, t_img *img, int x, int y)
{
	if (vars->map->map[y][x] == '1')
		make_img(img, vars->map->wall, (x * SCALE), (y * SCALE));
	if (vars->map->map[y][x] == '0')
		make_img(img, vars->map->floor, (x * SCALE), (y * SCALE));
	if (vars->map->map[y][x] == 'C')
		make_img(img, vars->map->collectible, (x * SCALE), (y * SCALE));
	if (vars->map->map[y][x] == 'E')
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

void	put_to_screen(t_vars *vars, t_img *img)
{
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}

void	render(t_vars *vars, t_img *img)
{
	render_map(vars, img);
	render_player(vars, img);//just put make img here to save 1 function??
	put_to_screen(vars, img);
}


int	main(int ac, char **av)
{
	t_map	map;//parser to check if it works (might not need to init map here)
	t_vars	vars;
	t_img	img;

	if (!parser(ac, av, &map))
		return (1);//this inits something
	mlx_init_vars(&vars, &map);
	init_img(&vars, &img, vars.width, vars.height);
	if (!player_init(&vars))
		return (1);
	map_init(&vars);
	render(&vars, &img);
	mlx_loop_hook(vars.mlx, handle_move, &vars);
	mlx_key_hook(vars.win, handle_input, &vars);
	mlx_hook(vars.win, 17, 1L << 17, clean, &vars);
	mlx_loop(vars.mlx);
}