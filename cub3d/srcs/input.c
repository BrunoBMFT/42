/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:33:44 by bruno             #+#    #+#             */
/*   Updated: 2025/01/07 02:19:36 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_game(t_data *data)
{
	clean_everything(data);
	exit (0);
	return (0);//for -wall -werror -wextra
}
//dir will be float dir_y, dir_x
bool	player_in_wall(t_data *data, int dir)//have to calculate if the next move is inside wall
{
	int posy = (int)data->player->pos_y;
	int posx = (int)data->player->pos_x;
	// printf("y %d\n", posy);
	// printf("x %d\n", posx);
	if (data->map[posy + dir][posx] == '1')
		return (true);
	return (false);
}

void	move_player(t_data *data, int dir)//dir will be float dir_y, dir_x
{
	// player_in_wall(data, dir);
	// printf("%f %d\n", data->player->pos_y, ft_split_wordcount(data->map));
	if (!player_in_wall(data, dir))
	{
		data->player->pos_y += dir;//0.25
		make_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win, data->frame->img, 0, 0);
	}
}
//dir will be dir_y and dir_x cause will need to know the collision for the angle we'll be travelling at

// todo test with the other directions now with dir y and dir x
// basically make everything like so long again, so i can test the directions and collisions are working
// then make a test case where i send it at an angle
// then implement the angle in the ray itself
//*    in hindsight, do i really need an angle ray? 
//*    subject does ask for it and i only need to know distance to the direction im facing to, and then int until the wall im facing
int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_game(data);
	if (keysym == 'w' || keysym == XK_Up){
		move_player(data, -1);
	}
	if (keysym == 's' || keysym == XK_Down){
		move_player(data, 1);
	}
	
	if (keysym == 'a' || keysym == XK_Left){
		//angles and shit
	}
	if (keysym == 'd' || keysym == XK_Right){
		//angles and shit
	}
	return (0);
}