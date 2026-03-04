#include "../includes/cub3d.h"

void	init_variables(t_data *data)
{
	data->file = NULL;
	data->map = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->frame.img = NULL;
	data->is_map = false;
}

bool	init(int ac, char **av, t_data *data)
{
	ft_bzero(data, sizeof(data));
	ft_bzero(data->paths, sizeof(data->paths));
	ft_bzero(data->sprites, sizeof(data->sprites));
	init_variables(data);
	if (!parser(ac, av, data))
		return (false);
	if (!player_init(data))
		return (false);
	data->map_active = false;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (error("Failed to initialize mlx"));
	data->win_width = WIN_WIDTH;
	data->win_height = WIN_HEIGHT;
	if (!init_imgs(data))
		return (false);
	data->win = mlx_new_window(data->mlx,
			data->win_width, data->win_height, "cub3d");
	return (true);
}
