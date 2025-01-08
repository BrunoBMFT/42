/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:57:32 by bruno             #+#    #+#             */
/*   Updated: 2025/01/08 02:04:50 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_pixel(t_img *img, int y, int x)
{
	char	*dst;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	put_pixel(t_img *img, int y, int x, int color)
{
	if (x < 0 || x > img->width || y < 0 || y > img->height)
        error(NULL, "pixel put in wrong place");
	char	*offset;
	offset = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}

void	make_frame(t_data *data, t_img *img, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			int color = get_pixel(img, i, j);
			put_pixel(data->frame, i + y, j + x, color);
			j++;
		}
		i++;
	}
}