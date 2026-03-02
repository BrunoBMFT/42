#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (!init(ac, av, &data))
		return (clean_everything(&data), 1);
	create_frame(&data);
	mlx_key_hook(data.win, input, &data);
	mlx_hook(data.win, 17, 1L << 17, clean_exit, &data);
	mlx_loop(data.mlx);
	return (0);
}
