#include "../includes/cub3d.h"


// void	walk_aux(t_data *data, float y_temp, float x_temp)
// {
// 	data->function_calls++;
// 	int	map_y;
// 	int	map_x;
// 	map_y = floor (y_temp);
// 	map_x = floor (x_temp);
// 	if ((data->map[map_y] && data->map[map_y][map_x]) &&
// 		data->map[map_y][map_x] != '1')
// 	{
// 		data->p_y = y_temp * SCALE;
// 		data->p_x = x_temp * SCALE;
// 	}
// }

// void	walk(t_data *data, int key_pressed)//remake to copy goncalo, rename key_pressed
// {
// 	//from parameters, get angle, which will be sent as WKEY, AKEY whatever
// 	//then do     angle_calc = (KEY - 1) * 90
// 	data->function_calls++;
// 	float	cos_value;
// 	float	sin_value;
// 	cos_value = W_STEP * cos(rad(data->p_angle));
// 	sin_value = W_STEP * sin(rad(data->p_angle));
// 	if (key_pressed == W_KEY)
// 		walk_aux(data, data->p_y / SCALE - cos_value,
// 			data->p_x / SCALE + sin_value);
// 	if (key_pressed == A_KEY)
// 		walk_aux(data, data->p_y / SCALE - sin_value,
// 			data->p_x / SCALE - cos_value);
// 	if (key_pressed == S_KEY)
// 		walk_aux(data, data->p_y / SCALE + cos_value,
// 			data->p_x / SCALE - sin_value);
// 	if (key_pressed == D_KEY)
// 		walk_aux(data, data->p_y / SCALE + sin_value,
// 			data->p_x / SCALE + cos_value);
// }

void	walk(t_data *data, int dir)//remake to copy goncalo, rename key_pressed
{
	data->function_calls++;

	float angle = data->p_angle + ((dir - 1) * 90);
	if (angle >= 360) angle -= 360;
	if (angle < 0) angle += 360;

	float x = data->p_x * cos(rad(angle)) / SCALE;
	float y = data->p_y * sin(rad(angle)) / SCALE;
	int	map_y = floor(x);
	int	map_x = floor(y);
	ft_printf("%d, %d, angle: %d\n", map_x, map_y, data->p_angle);
	if ((data->map[map_y] && data->map[map_y][map_x]) &&
		data->map[map_y][map_x] != '1') 
	{
		data->p_x = x * SCALE;
		data->p_y = y * SCALE;
	}

//aaaaaaa
	// float	cos_value;
	// float	sin_value;
	// cos_value = W_STEP * cos(rad(data->p_angle));
	// sin_value = W_STEP * sin(rad(data->p_angle));
	// if (key_pressed == W_KEY)
	// 	walk_aux(data, data->p_y / SCALE - cos_value,
	// 		data->p_x / SCALE + sin_value);
	// if (key_pressed == A_KEY)
	// 	walk_aux(data, data->p_y / SCALE - sin_value,
	// 		data->p_x / SCALE - cos_value);
	// if (key_pressed == S_KEY)
	// 	walk_aux(data, data->p_y / SCALE + cos_value,
	// 		data->p_x / SCALE - sin_value);
	// if (key_pressed == D_KEY)
	// 	walk_aux(data, data->p_y / SCALE + sin_value,
	// 		data->p_x / SCALE + cos_value);
}

void	pause_game(t_data *data)
{
	if (!data->paused) {
		mlx_mouse_show(data->mlx, data->win);
		data->paused = true;
		mlx_put_image_to_window(data->mlx, data->win, data->sprites[1].img, 0, 0);
	}
	else {
		mlx_mouse_hide(data->mlx, data->win);
		data->paused = false;
	}
}

// void	set_if_pressed(t_data *data, int keysym, int target, bool set)
// {
// 	if (keysym == target)
// }

int	key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		clean_exit(data, 0);
	else if (keysym == 'p')
		pause_game(data);
	
	// setIfPressed(data, keysym, XK_Right, true);

	else if (keysym == XK_Right)
		data->inputs[RIGHT_KEY] = true;
	else if (keysym == XK_Left)
		data->inputs[LEFT_KEY] = true;
	else if (keysym == 'w')
		data->inputs[W_KEY] = true;
	else if (keysym == 'a')
		data->inputs[A_KEY] = true;
	else if (keysym == 's')
		data->inputs[S_KEY] = true;
	else if (keysym == 'd')
		data->inputs[D_KEY] = true;
	return (0);
}

int	key_release(int keysym, t_data *data)
{
	if (keysym == XK_Right)
		data->inputs[RIGHT_KEY] = false;
	else if (keysym == XK_Left)
		data->inputs[LEFT_KEY] = false;
	else if (keysym == 'w')
		data->inputs[W_KEY] = false;
	else if (keysym == 'a')
		data->inputs[A_KEY] = false;
	else if (keysym == 's')
		data->inputs[S_KEY] = false;
	else if (keysym == 'd')
		data->inputs[D_KEY] = false;
	return (0);
}

void	fps_count(t_data *data)
{
	float elapsed = get_time() - data->start;
	if (elapsed > 50) {
		printf("fps %.2f\n", (float)data->frame_count / elapsed * 1000);
		data->frame_count = 0;
		data->start = get_time();
	}
}

void	move_if_player_moving(t_data *data, bool was_key_pressed, int key)
{
	if (was_key_pressed)
		walk(data, key);
}

int	game_frame(t_data *data)//rename and put in a different folder
{
	fps_count(data);
	if (data->paused)
		return (0);
	if (data->inputs[RIGHT_KEY])//make modular
		data->p_angle += A_STEP;
	if (data->inputs[LEFT_KEY])
		data->p_angle -= A_STEP;
	move_if_player_moving(data, data->inputs[W_KEY], W_KEY);
	move_if_player_moving(data, data->inputs[A_KEY], A_KEY);
	move_if_player_moving(data, data->inputs[S_KEY], S_KEY);
	move_if_player_moving(data, data->inputs[D_KEY], D_KEY);
	create_frame(data);
	return (0);
}

int	mouse_movement(int x, int y, t_data	*data)//make this a triggerable thing
{
	int	dif;

	(void)y;
	if (data->paused)
		return (0);
	dif = abs(data->win_width- x);
	if (x > (data->win_width / 2))
		data->p_angle += A_STEP;
	else if (x < (data->win_width / 2))
		data->p_angle -= A_STEP;
	mlx_mouse_move(data->mlx, data->win, data->win_width / 2, data->win_height / 2);
	return (0);
}