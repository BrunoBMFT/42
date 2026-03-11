#include "../includes/cub3d.h"

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	init_variables(t_data *data)
{
	data->file = NULL;
	data->map = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->frame.img = NULL;
	data->is_map = false;
	ft_bzero(data->inputs, sizeof(data->inputs));
	// data->in_right = false;
	// data->in_left = false;
	// data->in_w = false;
	// data->in_a = false;
	// data->in_s = false;
	// data->in_d = false;
	data->frame_count = 0;
	data->function_calls = 0;
	data->start = get_time();
	data->paused = false;
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
