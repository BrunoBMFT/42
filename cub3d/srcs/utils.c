/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:02:49 by bruno             #+#    #+#             */
/*   Updated: 2025/03/27 17:04:49 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//put a limit for size? like if (y > win_width)
void	put_pixel(t_img *img, int y, int x, int color)
{
	char	*offset;

	offset = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}

//find better way for pixels, maybe make the scale onto put_pixel itself?
void	loop_map(t_data *data, int y, int x, int color)
{
	int	i = 0;
	while (i < SCALE)
	{
		int j = 0;
		while (j < SCALE)
		{
			put_pixel(&data->frame, (y * SCALE) + i, (x * SCALE) + j, color);
			j++;
		}
		i++;
	}
}

void	create_map(t_data *data)
{
	int	y = 0;
	while (data->map[y])
	{
		int x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				loop_map(data, y, x, WHITE);
			else if (data->map[y][x] == '0')
				loop_map(data, y, x, GREY);
			else if (ft_strchr("NESW", data->map[y][x]))
			{
				put_pixel(&data->frame, y, x, GREEN);
				data->p_y = y;
				data->p_x = x;
			}
			x++;
		}
		y++;
	}
}

int	input(int keysym, t_data *data)
{
	if (keysym == XK_Escape){	
		clean_everything(data);
		exit(0);
	}
	return (0);
}
