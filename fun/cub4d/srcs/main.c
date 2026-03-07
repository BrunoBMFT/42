#include "../includes/cub3d.h"
void	walk_aux(t_data *data, float y_temp, float x_temp)
{
	int	map_y;
	int	map_x;

	map_y = floor (y_temp);
	map_x = floor (x_temp);
	if ((data->map[map_y] && data->map[map_y][map_x]) &&
		data->map[map_y][map_x] != '1')
	{
		data->p_y = y_temp * SCALE;
		data->p_x = x_temp * SCALE;
	}
}

void	walk(t_data *data, int keysym)//remake to copy goncalo
{
	float	cos_value;
	float	sin_value;

	cos_value = W_STEP * cos(rad(data->p_angle));
	sin_value = W_STEP * sin(rad(data->p_angle));
	if (keysym == 'w')
		walk_aux(data, data->p_y / SCALE - cos_value,
			data->p_x / SCALE + sin_value);
	if (keysym == 's')
		walk_aux(data, data->p_y / SCALE + cos_value,
			data->p_x / SCALE - sin_value);
	if (keysym == 'a')
		walk_aux(data, data->p_y / SCALE - sin_value,
			data->p_x / SCALE - cos_value);
	if (keysym == 'd')
		walk_aux(data, data->p_y / SCALE + sin_value,
			data->p_x / SCALE + cos_value);
}



int	key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		clean_exit(data, 0);
	else if (keysym == XK_Right)
		data->in_right = true;
	else if (keysym == XK_Left)
		data->in_left = true;
	else if (keysym == 'w')
		data->in_w = true;
	else if (keysym == 'a')
		data->in_a = true;
	else if (keysym == 's')
		data->in_s = true;
	else if (keysym == 'd')
		data->in_d = true;
	return (0);
}

int	key_release(int keysym, t_data *data)
{
	if (keysym == XK_Right)
		data->in_right = false;
	else if (keysym == XK_Left)
		data->in_left = false;
	else if (keysym == 'w')
		data->in_w = false;
	else if (keysym == 'a')
		data->in_a = false;
	else if (keysym == 's')
		data->in_s = false;
	else if (keysym == 'd')
		data->in_d = false;
	return (0);
}

int	move_player(t_data *data)
{
	if (data->in_right)
		data->p_angle += A_STEP;
	if (data->in_left)
		data->p_angle -= A_STEP;
	if (data->in_w)
		walk(data, 'w');
	if (data->in_a)
		walk(data, 'a');
	if (data->in_s)
		walk(data, 's');
	if (data->in_d)
		walk(data, 'd');
	create_frame(data);
	return (0);
}


int	main(int ac, char **av)
{
	t_data	data;

	if (!init(ac, av, &data))
		clean_exit(&data, 1);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_loop_hook(data.mlx, move_player, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, mlx_clean_exit, &data);
	mlx_loop(data.mlx);
	return (0);
}
