/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:33:44 by bruno             #+#    #+#             */
/*   Updated: 2025/01/06 18:20:54 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_game(t_data *data)
{
	clean_everything(data);
	exit (0);
	return (0);//for -wall -werror -wextra
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_game(data);
	if (keysym == 'w' || keysym == XK_Up){
		data->player->pos_y -= 0.25;
		make_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win, data->frame->img, 0, 0);
	}
	if (keysym == 's' || keysym == XK_Down){
		data->player->pos_y += 0.25;
		make_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win, data->frame->img, 0, 0);
	}
	
	if (keysym == 'a' || keysym == XK_Left){
		//angles and shit
	}
	if (keysym == 'd' || keysym == XK_Right){
		//angles and shit
	}
	return (0);
}