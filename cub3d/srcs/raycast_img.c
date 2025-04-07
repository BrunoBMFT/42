/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:58:59 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/07 19:59:14 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	put_pixel(t_data *data, int y, int x, int color)
{
	char	*offset;

	if (y < 0 || x < 0 || y > data->win_height || x > data->win_width)
		return ;
	offset = data->frame.addr + (y * data->frame.line_len + x
			* (data->frame.bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}
