/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:04:14 by bruno             #+#    #+#             */
/*   Updated: 2025/04/07 20:04:41 by brfernan         ###   ########.fr       */
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
	data->door_opened = false;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (error("Failed to initialize mlx"));
	data->win_width = WIN_WIDTH;
	data->win_height = WIN_HEIGHT;
	if (!init_imgs(data))
		return (false);
	data->win = mlx_new_window(data->mlx,
			data->win_width, data->win_height, "cub3d");
	return (true);
}
