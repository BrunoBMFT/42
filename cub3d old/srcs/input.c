/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:33:44 by bruno             #+#    #+#             */
/*   Updated: 2025/01/08 02:35:22 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_game(t_data *data)
{
	clean_everything(data);
	exit (0);
	return (0);//for -wall -werror -wextra
}
// maybe i can send int as the absolute pixel position of 1 pixel 
// of player and then multiply with scale to check if its inside map

// do an approximation of value
// have a function that returns an int that is the result of the float being approximated to the closest int
bool	player_in_wall(t_data *data, int dir_y, int dir_x)//have to calculate if the next move is inside wall
{
	int posy = (int)roundf(data->player->y + dir_y);
	int posx = (int)roundf(data->player->x + dir_x);
	if (data->map[posy][posx] == '1')
		return (true);
	return (false);
}

//take care of angles

void	move_player(t_data *data, float dir_y, float dir_x)//dir will be float dir_y, dir_x
{
	data->player->x += dir_x;//0.25
	make_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->frame->img, 0, 0);
	// printf("dir y %f x %f\n", dir_y, dir_x);
	// if (!player_in_wall(data, (int)dir_y, (int)dir_x))//sends 0 when its less than 1 (0.5)
	// {
	// 	data->player->y += dir_y;//0.25
	// 	data->player->x += dir_x;//0.25
	// 	make_minimap(data);
	// 	mlx_put_image_to_window(data->mlx, data->win, data->frame->img, 0, 0);
	// }
}


// todo take care of movement after
// then make a test case where i send it at an angle
int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_game(data);
	if (keysym == 'w' || keysym == XK_Up){
		move_player(data, -0.25, 0);
	}
	if (keysym == 's' || keysym == XK_Down){
		move_player(data, 0.25, 0);
	}
	
	if (keysym == 'a' || keysym == XK_Left){
		//angles and shit
	}
	if (keysym == 'd' || keysym == XK_Right){
		//angles and shit
	}
	// if (keysym == 'f') {
	// 	data->player->y = 2.5;
	// 	data->player->x = 2.5;
		
	// 	raycast(data);
	// 	make_minimap(data);
	// 	mlx_put_image_to_window(data->mlx, data->win, data->frame->img, 0, 0);
	// 	//angles and shit
	// }
	return (0);
}