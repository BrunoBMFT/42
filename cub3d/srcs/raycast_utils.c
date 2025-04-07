/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:46:19 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/07 14:07:33 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	angle_correct(float *angle, int *dir, bool is_h)
{
	while (*angle < 0)
		*angle += 360;
	while (*angle >= 360)
		*angle -= 360;
	if (is_h)
	{
		*angle = 180 - *angle;
		if (*angle >= 0 && *angle <= 180)
			*dir = 1;
		else
			*dir = -1;
	}
	else
	{
		*angle = 360 - *angle;
		if (*angle >= 90 && *angle <= 270)
			*dir = 1;
		else
			*dir = -1;
	}
}

int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

// printf("%d %d\n", y, x);
// printf("putpixel out of bounds\n");
void	put_pixel(t_data *data, int y, int x, int color)
{
	char	*offset;

	if (y < 0 || x < 0 || y > data->win_height || x > data->win_width)
		return ;
	offset = data->frame.addr + (y * data->frame.line_len + x
			* (data->frame.bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}

float	rad(float deg)
{
	return (deg * PI / 180);
}
