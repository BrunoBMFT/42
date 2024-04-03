/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:45:17 by bruno             #+#    #+#             */
/*   Updated: 2024/04/03 19:31:13 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//need to make a check for exit and if all C are collectible
//need to make check if game is rectangular
//need to check if player is inbounds (caught in flood)


int	free_windows(t_data *vars)
{
//	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(1);
}
void	clean_everything(t_map *map, t_data *vars)
{
	free_parser(map);
	free_windows(vars);
}
int	button_press(int button, int x, int y)
{
	if (button == 1)
		printf("Left mouse button pressed at (%d, %d)\n", x, y);
	else if (button == 3)
		printf("Right mouse button pressed at (%d, %d)\n", x, y);
	return (0);
}
int	handle_input(int keysym, t_data *vars)
{
	if (keysym == XK_Escape)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		free_windows(vars);
	}
	printf("The %d key has been pressed\n\n", keysym);
	return (0);
}

int	get_pixel(t_img * img, int x, int y)
{
	char	*dst;
	dst = img->address + (y * img->line_len + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	my_pixel_put(t_img * img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	create_img(t_img *img, t_img src, int x, int y)
{
	int		i = 0;
	unsigned int	color;

	while (i < src.width)
	{
		int j = 0;
		while (j < src.height)
		{
			color = get_pixel(&src, i, j);
			if (color != TRANSPARENT)
				my_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	render_map_condition(t_data *vars, t_img *img, int x, int y)
{
	if (vars->map->map[y][x] == '1')
	{
		create_img(img, vars->map->wall, (x * SCALE)
				+ BORDER, (y * SCALE) + BORDER);
	}
	/*else if (vars->map->map[y][x] == '0')
	{
		create_img(img, vars->map->wall, (x * SCALE)
				+ BORDER, (y * SCALE) + BORDER);
	}
	else if (vars->map->map[y][x] == 'C')
	{
		create_img(img, vars->map->wall, (x * SCALE)
				+ BORDER, (y * SCALE) + BORDER);
	}
	else if (vars->map->map[y][x] == 'E')
	{
		create_img(img, vars->map->wall, (x * SCALE)
				+ BORDER, (y * SCALE) + BORDER);
	}*/
}

void	render_map(t_data *vars, t_img *src)
{
	int	y = 0;
	
	while (vars->map->map[y])
	{
		int x = 0;
		while (x < vars->map->map[y][x])
		{
			render_map_condition(vars, src, x, y);
			x++;
		}
		y++;
	}
}

void	map_init(t_data *vars)
{
	vars->map->map = NULL;//maybe not needed?
	vars->map->visited = NULL;//not needed

	//below is just for wall
	vars->map->wall.img = mlx_xpm_file_to_image(vars->mlx, "./assets/edited/wall.xpm",
				&vars->map->wall.width, &vars->map->wall.height);
	if (vars->map->wall.img == NULL)
	{
		ft_putendl_fd("error invalid wall", 1);
		exit(1);
	}
	vars->map->wall.address = mlx_get_data_addr(vars->map->wall.img,
					&vars->map->wall.bits_per_pixel, &vars->map->wall.line_len,
					&vars->map->wall.endian);
}

void	mlx_init_vars(t_data *vars, t_map *map)
{
	int	width;
	int height;

	vars->map = map;
	vars->width = map->col * SCALE + BORDER * 2;
	vars->height = map->row * SCALE + BORDER * 2;
	if (!(vars->mlx = mlx_init()))
		clean_everything(map, vars);
	mlx_get_screen_size(vars->mlx, &width, &height);
	if (!(vars->win = mlx_new_window(vars->mlx, vars->width, vars->height, "so_long")))
		clean_everything(map, vars);
}

void	mlx_init_image(t_data *vars, t_img *img, int width, int height)
{
	img->img = mlx_new_image(vars->mlx, width, height);
	img->address = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_len, &img->endian);
	vars->win = img;
}

int	main(int ac, char **av)
{
	t_map	map;
	t_data vars;//change name
//	char	*path = "./assets/edited/wall_north.xpm";

	init(&map);//just for parser
	if (!parser(ac, av, &map))
		return (ft_printf("reeee"), clean_everything(&map, &vars), 1);

	t_img img;
	mlx_init_vars(&vars, &map);
	mlx_init_image(&vars, &img, vars.width, vars.height);
	map_init(&vars);
	
//	vars.img = mlx_xpm_file_to_image(vars.mlx, path, &img_width, &img_height);
//	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);

	render_map(&vars, vars.map->wall.img);





	mlx_key_hook(vars.win, handle_input, &vars);
	mlx_hook(vars.win, ButtonPress, ButtonPressMask, &button_press, &vars);
	mlx_hook(vars.win, 17, 1L << 17, free_windows, &vars);
	
	mlx_loop(vars.mlx);

	free_parser(&map);
}