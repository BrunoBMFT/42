#include "../includes/cub3d.h"

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
// 	create_background(data);
// 	raycast(data);
// 	if (!ft_is_even(data->map_active))
// 		create_map(data);
// 	mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_data	data;

	if (!init(ac, av, &data))
		return (clean_everything(&data), 1);
	create_frame(&data);
	mlx_key_hook(data.win, input, &data);
	// mlx_hook(data.win, MotionNotify, PointerMotionMask,
	// 	mouse_movement, &data);
	mlx_hook(data.win, 17, 1L << 17, clean_exit, &data);
	mlx_loop(data.mlx);
	return (0);
}
