#include "../includes/cub3d.h"

// int	input(int keysym, t_data *data)
// {
// 	if (keysym == XK_Escape)
// 		clean_exit(data, 0);
// 	else if (ft_strchr("wasdfm", keysym)
// 		|| keysym == XK_Left || keysym == XK_Right)
// 	{
// 		if (keysym == XK_Right)
// 			data->p_angle += A_STEP;
// 		else if (keysym == XK_Left)
// 			data->p_angle -= A_STEP;
// 		else if (ft_strchr("wasd", keysym))
// 			walk(data, keysym);
// 		create_frame(data);
// 	}
// 	return (0);
// }



// int	mouse_movement(int x, int y, t_data	*data)
// {
// 	int	dif;
// 	(void)y;
// 	dif = abs(data->win_width- x);
// 	if (x > (data->win_width / 2))
// 		data->p_angle += (dif / 200);
// 	else if (x < (data->win_width / 2))
// 		data->p_angle-= dif / 200;
// 	mlx_mouse_move(data->mlx, data->win, data->win_width / 2,
// 		data->win_height / 2);
// 		create_frame(data);
// }
// mlx_hook(data.win, MotionNotify, PointerMotionMask,
// 	mouse_movement, &data);