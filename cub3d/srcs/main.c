/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/04/03 20:25:04 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	angle_correct(float *angle)
{
	while (*angle < 0)
		*angle += 360;
	while (*angle >= 360)
		*angle -= 360;
}

void	loop_player2(t_data *data, float y, float x, int color)
{
	int	i = 0;
	while (i < SCALE / 4)
	{
		int j = 0;
		while (j < SCALE / 4)
		{
			put_pixel(data, y + i - 2, x + j - 2, color);
			j++;
		}
		i++;
	}
}

void	check_steps(float angle, float *y_step, float *x_step)
{
	int	y_dir;
	int	x_dir;
	if ((angle > 315 && angle <= 360) || (angle >= 0 && angle <= 135)){
		y_dir = -1;
		x_dir = 1;
	}
	else if ((angle > 135 && angle <= 315)){
		y_dir = 1;
		x_dir = -1;
	}
	if ((angle >= 0 && angle <= 45) || (angle > 135 && angle <= 225)
	|| (angle > 315 && angle <= 360)){
		*x_step = x_dir * tan(rad(angle));
		*y_step = y_dir;
	}
	else if ((angle > 45 && angle <= 135) || (angle > 225 && angle <= 315)){
		*y_step = y_dir / tan(rad(angle));
		*x_step = x_dir;
	}
}
// this function could be better doing the steps
// have the h_inter and v_inter
float	find_distance(t_data *data, float angle)
{
	float	y_step;
	float	x_step;
	angle_correct(&angle);	
	check_steps(angle, &y_step, &x_step);
	float y = data->p_y * SCALE, x = data->p_x * SCALE;//moves through map
	int map_y = floor (y / SCALE);//coord in map
	int map_x = floor (x / SCALE);
	// put_pixel(data, y, x, GREEN);
	//check for y = 0, x = 0, outside map
	while (data->map[map_y] && data->map[map_y][map_x] && data->map[map_y][map_x] != '1')
	{
		map_y = floor(y / SCALE);
		map_x = floor(x / SCALE);
		y += y_step;
		x += x_step;
		if (y < 0 || x < 0 || y > data->win_height || x > data->win_width)//needed?
			break ;
		put_pixel(data, y, x, GREEN);
	}
	float dif_y = data->p_y * SCALE - y, dif_x = data->p_x * SCALE - x;
	return (sqrt(pow(dif_y, 2) + pow(dif_x, 2)));
}


// float	find_h_inter(t_data *data, float angle)
// {
// 	angle_correct(&angle);
// 	int	y_dir;
// 	int	x_dir;
// 	if ((angle > 315 && angle <= 360) || (angle >= 0 && angle <= 135)){
// 		y_dir = -1;
// 		x_dir = 1;
// 	}
// 	else if ((angle > 135 && angle <= 315)){
// 		y_dir = 1;
// 		x_dir = -1;
// 	}
// 	// float y = data->p_y * SCALE, x = data->p_x * SCALE;//moves through map
// 	//y will be already intercepting a int
// 	//x will already be the angle of this
// 	float	y_step = SCALE * y_dir;
// 	float	x_step = SCALE / tan(rad(angle)) * x_dir;
// 	float y = floor(data->p_y) * SCALE;
// 	float x = data->p_x + (y - data->p_y) / tan(rad(angle));
// 	int map_y = floor (y / SCALE);//coord in map
// 	int map_x = floor (x / SCALE);
// 	while (1)
// 	{
// 		map_y = floor(y / SCALE);
// 		map_x = floor(x / SCALE);
// 		if (map_y < 0 || map_x < 0 || map_y >= data->win_height || map_x >= data->win_width)
//             break;
//         if (data->map[map_y][map_x] == '1')
//             break;
// 		y += y_step;
// 		x += x_step;
// 		if (y < 0 || x < 0 || y > data->win_height || x > data->win_width)//needed?
// 			break ;
// 		put_pixel(data, y, x, GREEN);
// 	}
// 	float dif_y = data->p_y - y, dif_x = data->p_x - x;
// 	return (sqrt(pow(dif_y, 2) + pow(dif_x, 2)));
// }

float	find_v_inter(t_data *data, float angle)
{
	angle_correct(&angle);
	int	y_dir;
	int	x_dir;
	if ((angle > 315 && angle <= 360) || (angle >= 0 && angle <= 135)){
		y_dir = -1;
		x_dir = 1;
	}
	else if ((angle > 135 && angle <= 315)){
		y_dir = 1;
		x_dir = -1;
	}

	// ! CHATGPT IS RIGHT, check latest
	float	x_step = SCALE * x_dir;
	float	y_step = SCALE * tan(rad(angle)) * y_dir;//use x_step instead of SCALE
	
	float x = floor(data->p_x / SCALE) * SCALE;
	if (x_dir == 1)
		x+= SCALE;
	float y = data->p_y + (x - data->p_x) * tan(rad(angle));
	// put_pixel(data, y, x, GREEN);
	
	int map_y = floor (y / SCALE);//coord in map
	int map_x = floor (x / SCALE);
	while (1)
	{
		map_y = floor(y / SCALE);
		map_x = floor(x / SCALE);
		if (map_y < 0 || map_x < 0 || map_y >= data->win_height || map_x >= data->win_width)
            break;
        if (data->map[map_y][map_x] == '1')
            break;
		y += y_step;
		x += x_step;
		if (y < 0 || x < 0 || y > data->win_height || x > data->win_width)//needed?
			break ;
		// put_pixel(data, y, x, GREEN);
	}
	float dif_y = data->p_y - y, dif_x = data->p_x - x;
	return (sqrt(pow(dif_y, 2) + pow(dif_x, 2)));
}


//missing the fisheye fix
void	draw_wall_section(t_data *data, float hyp, int i)
{
	float dist_to_plane = (data->win_width / 2) / tan(rad(64) / 2);
	int height = SCALE * dist_to_plane / hyp;

	int top = (data->win_height / 2) - (height / 2);
	int bot = (data->win_height / 2) + (height / 2);
	
	if (top < 0) top = 0;
	if (bot > data->win_height) bot = data->win_height;
	int y = top;
	while (y < bot)
	{
		int x = 0;
		while (x < 20)
		{
			put_pixel(data, y, i + x, RED);
			x++;
		}
		y++;
	}

}

void	raycast(t_data *data)
{
	int i = 0;
	float angle = data->p_angle - 32;//related to facing angle
	while (i < data->win_width)
	{
		// float hyp = find_distance(data, angle);
		// draw_wall_section(data, hyp, i);
		//do inters
		float v = find_v_inter(data, angle);
		// float h = find_h_inter(data, angle);
		// if (v < h)
			draw_wall_section(data, v, i);
		// else
		// 	draw_wall_section(data, h, i);
		
		
		
		i += 20;//this is the player_fov degree by degree, 20
		angle++;
	}
}

void	create_frame(t_data *data)
{
	clear_img(data);
	create_map(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
}



int	main(int ac, char **av)
{
	t_data data;

	if (!init(ac, av, &data))
		return (clean_everything(&data), 1);
	data.p_angle = 0;

	create_frame(&data);
	
	mlx_key_hook(data.win, input, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
