/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:41:39 by bruno             #+#    #+#             */
/*   Updated: 2024/04/20 16:41:54 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long.h"

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

