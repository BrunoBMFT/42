/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 03:51:51 by brfernan          #+#    #+#             */
/*   Updated: 2025/05/11 03:52:05 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_wall_height(t_data *data, float hyp, float angle)
{
	return ((SCALE * (data->win_width / 2) / tan(rad(FOV) / 2))
		/ (hyp * cos(rad(angle - data->p_angle))));
}

void	limit_check(t_data *data, int *top, int *bot)
{
	if (*top < 0)
		*top = 0;
	if (*bot > data->win_height)
		*bot = data->win_height;
}

int	get_text_x(t_data *data, t_coord coord, bool vert)
{
	if (vert)
		return (fmodf(coord.y, SCALE) * data->north.width / SCALE);
	return (fmodf(coord.x, SCALE) * data->north.width / SCALE);
}

int	get_color(t_data *data, t_coord coord, t_coord texture, bool vert)
{
	if (vert)
	{
		if (coord.x > data->p_x)
			return (get_pixel(&data->east, texture.x, texture.y));
		else
			return (get_pixel(&data->west, texture.x, texture.y));
	}
	if (coord.y > data->p_y)
		return (get_pixel(&data->south, texture.x, texture.y));
	return (get_pixel(&data->north, texture.x, texture.y));
}

void	draw_wall_section(t_data *data, t_draw *info)
{
	int		height;
	int		top;
	int		bot;
	float	tex_pos;
	t_coord	texture;

	height = get_wall_height(data, info->hyp, info->angle);
	top = (data->win_height / 2) - (height / 2);
	bot = (data->win_height / 2) + (height / 2);
	limit_check(data, &top, &bot);
	texture.x = get_text_x(data, info->coord, info->vert);
	tex_pos = (top - data->win_height / 2 + height / 2)
		* (float)data->north.height / height;
	while (top < bot)
	{
		texture.y = tex_pos;
		if (texture.y >= data->north.height)
			texture.y = data->north.height - 1;
		put_pixel(data, top, info->section,
			get_color(data, info->coord, texture, info->vert));
		tex_pos += (float)data->north.height / height;
		top++;
	}
}
