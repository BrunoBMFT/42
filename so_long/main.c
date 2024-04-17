/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:18:28 by bruno             #+#    #+#             */
/*   Updated: 2024/04/17 19:18:02 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long.h"
// ! turn every function to bool
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
	if (!img->img)//use putendl + defined string
		ft_putstr("new image failed");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endian);
//	vars->load_img = img;
}

void	map_init(t_vars *vars)
{
	//wall_init(vars);
	//floor_init(vars);
	vars->map->wall.img = mlx_xpm_file_to_image(vars->mlx,
			"./assets/CENTER.xpm", &vars->map->wall.width,
			&vars->map->wall.height);
	if (vars->map->wall.img == NULL)
		ft_putendl(INV_WALL);
	vars->map->wall.addr = mlx_get_data_addr(vars->map->wall.img,
			&vars->map->wall.bits_per_pixel, &vars->map->wall.line_len,
			&vars->map->wall.endian);
}

int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	make_img(t_img *img, t_img src, int x, int y)//makes each block
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
//			if (color != TRANSvarsENT)
				put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
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
//			render_map_condition(vars, img, x, y);
			make_img(img, vars->map->wall, (x * SCALE), (y * SCALE));
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
//	render_packman(vars, img);
	put_to_screen(vars, img);
}

void	freemap(t_map *map)//make my own
{
	int	ctd;

	ctd = 0;
	while (map->map[ctd])
		free(map->map[ctd++]);
	free(map->map);
	exit(0);
}

int	clean(t_vars *vars)//make my own
{
//	int	ctd = 0;
//	while (ctd < 16)
//		mlx_destroy_image(vars->mlx, vars->packman->img[ctd++].img);
//	mlx_destroy_image(vars->mlx, vars->load_img->img);
	if (vars->map)
		mlx_destroy_image(vars->mlx, vars->map->wall.img);
//	mlx_destroy_image(vars->mlx, vars->map->floor.img);
//	mlx_destroy_image(vars->mlx, vars->map->collectible.img);
//	mlx_destroy_image(vars->mlx, vars->map->exit.img);
//	mlx_destroy_image(vars->mlx, vars->map->border_vertical.img);
//	mlx_destroy_image(vars->mlx, vars->map->border_horizontal.img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
//	free(vars->packman);
	free(vars->mlx);
	freemap(vars->map);
	return (0);
}

int	handle_input(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape)
		clean(vars);
	return (0);
}

int	main(int ac, char **av)
{
	t_map	map;//parser to check if it works (might not need to init map here)
	t_vars	vars;
	t_img	img;

	parser(ac, av, &map);
	mlx_init_vars(&vars, &map);
	init_img(&vars, &img, vars.width, vars.height);
//	pacman_init(&vars);
	map_init(&vars);
	render(&vars, &img);
	mlx_hook(vars.win, 17, 1L << 17, clean, &vars);
	mlx_key_hook(vars.win, handle_input, &vars);
	mlx_loop(vars.mlx);
	ft_putstr("\nno crash here\n");
}