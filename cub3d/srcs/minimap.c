/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:15:33 by bruno             #+#    #+#             */
/*   Updated: 2025/01/06 04:13:19 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_minimap(t_data *data, int x, int y)//make something that can initialize images in a function
{
	data->minimap = malloc(sizeof(t_img));
	if (!data->minimap)
		error(data, "Minimap image allocation failed");
	data->mini_scale = 1;
	data->minimap->width = data->frame->width / data->mini_scale;
	data->minimap->height = data->frame->height / data->mini_scale;
	data->minimap->img = mlx_new_image(data->mlx, data->minimap->width, data->minimap->height);
	if (!data->minimap->img)
		error(data, "Minimap image failed");
	data->minimap->addr = mlx_get_data_addr(data->minimap->img, &data->minimap->bits_per_pixel,
			&data->minimap->line_len, &data->minimap->endian);
}

void	make_minimap_pixel(t_data *data, int y, int x, int color)//what changes for scale is this one
{
	int	i;
	int	j;

	i = 0;
//todo big problem with border, now when player goes through it, it paints it, since nothing is telling
//todo the minimap that its supposed to be black
	while (i < (SCALE / data->mini_scale)- 2)
	{
		j = 0;
		while (j < (SCALE / data->mini_scale) - 2)
		{
			put_pixel(data->minimap, i + (y * SCALE / data->mini_scale), j + (x * SCALE / data->mini_scale), color);
			j++;
		}
		i++;
	}
}

void	make_player_pixel(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < (SCALE / data->mini_scale / 8))
	{
		j = 0;
		while (j < (SCALE / data->mini_scale / 8))
		{
			put_pixel(data->minimap, i + (data->player->y * SCALE / data->mini_scale)
			, j + (data->player->x * SCALE / data->mini_scale), GREEN);
			j++;
		}
		i++;
	}
}

void	make_minimap(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				make_minimap_pixel(data, y, x, BLUE);
			else if (data->map[y][x] == '0' || ft_strchr("NESW", data->map[y][x]))
				make_minimap_pixel(data, y, x, WHITE);
			else
				make_minimap_pixel(data, y, x, PINK);
			x++;
		}
		y++;
	}
	make_player_pixel(data);
	
	make_frame(data, data->minimap, 0, 0);
}