/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:04:14 by bruno             #+#    #+#             */
/*   Updated: 2025/04/07 04:15:19 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_variables(t_data *data)
{
	data->file = NULL;
	data->map = NULL;
	data->path_north = NULL;
	data->path_east = NULL;
	data->path_south = NULL;
	data->path_west = NULL;
	data->path_floor = NULL;
	data->path_ceiling = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->north.img = NULL;
	data->east.img = NULL;
	data->south.img = NULL;
	data->west.img = NULL;
	data->frame.img = NULL;
}

bool	init_texture_img(t_data *data, t_img *texture, char *img_src)
{
	texture->img = NULL;
	texture->img = mlx_xpm_file_to_image(data->mlx,
			img_src, &texture->width, &texture->height);
	if (!texture->img)
		return (error("A image failed to init"));
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_len, &texture->endian);
	if (!texture->addr)
		return (error("An image address failed init"));
	return (true);
}

bool	init_imgs(t_data *data)
{
	if (!init_texture_img(data, &data->north, "./sprites/north.xpm"))
		return (false);
	if (!init_texture_img(data, &data->east, "./sprites/east.xpm"))
		return (false);
	if (!init_texture_img(data, &data->south, "./sprites/south.xpm"))
		return (false);
	if (!init_texture_img(data, &data->west, "./sprites/west.xpm"))
		return (false);
	data->frame.img = mlx_new_image(data->mlx,
			data->win_width, data->win_height);
	if (!data->frame.img)
		return (error("Frame failed initializing"));
	data->frame.addr = mlx_get_data_addr(data->frame.img,
			&data->frame.bits_per_pixel,
			&data->frame.line_len, &data->frame.endian);
	if (!data->frame.addr)
		return (error("Frame address failed initializing"));
	return (true);
}

void	player_angle_init(t_data *data, int facing)
{
	if (facing == 'N')
		data->p_angle = 0;
	else if (facing == 'E')
		data->p_angle = 90;
	else if (facing == 'S')
		data->p_angle = 180;
	else if (facing == 'W')
		data->p_angle = 270;
	data->door_opened = false;
}

bool	player_init(t_data *data)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NESW", data->map[y][x]))
			{
				data->p_y = y * SCALE;
				data->p_x = x * SCALE;
				player_angle_init(data, data->map[y][x]);
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (error("Invalid player"));
	return (true);
}

int	parse_rgb(const char *str)
{
	int	i;
	int	start;
	int	red;
	int	green;
	int	blue;

	i = 0;
	start = 0;
	while (str[i] && str[i] != ',')
		i++;
	red = ft_atoi(&str[start]);
	start = ++i;
	while (str[i] && str[i] != ',')
		i++;
	green = ft_atoi(&str[start]);
	start = ++i;
	blue = ft_atoi(&str[start]);
	return ((red << 16) | (green << 8) | blue);
}

void	init_colors(t_data *data)
{
	data->color_floor = parse_rgb(data->path_floor);
	data->color_ceiling = parse_rgb(data->path_ceiling);
}

bool	init(int ac, char **av, t_data *data)
{
	init_variables(data);
	if (!parser(ac, av, data))
		return (false);
	if (!player_init(data))
		return (false);
	init_colors(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (error("Failed to initialize mlx"));
	data->win_width = 1280;
	data->win_height = 720;
	if (!init_imgs(data))
		return (false);
	data->win = mlx_new_window(data->mlx,
			data->win_width, data->win_height, "cub3d");
	return (true);
}
