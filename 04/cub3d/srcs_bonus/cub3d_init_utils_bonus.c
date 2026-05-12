/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:04:53 by brfernan          #+#    #+#             */
/*   Updated: 2025/05/12 15:01:53 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	if (!init_texture_img(data, &data->north, data->path_north))
		return (false);
	if (!init_texture_img(data, &data->east, data->path_east))
		return (false);
	if (!init_texture_img(data, &data->south, data->path_south))
		return (false);
	if (!init_texture_img(data, &data->west, data->path_west))
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
				count++;
				player_angle_init(data, data->map[y][x]);
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (error("Invalid player"));
	return (true);
}
