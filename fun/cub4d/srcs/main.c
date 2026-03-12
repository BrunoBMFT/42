#include "../includes/cub3d.h"

//add button(x, y, size_x, size_y, function)

int	main(int ac, char **av)
{
	t_data	data;

	if (!init(ac, av, &data))
		clean_exit(&data, 1);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_loop_hook(data.mlx, game_frame, &data);
	// mlx_hook(data.win, MotionNotify, PointerMotionMask, mouse_movement, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, mlx_clean_exit, &data);
	mlx_loop(data.mlx);
	return (0);
}
