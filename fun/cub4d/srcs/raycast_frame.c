#include "../includes/cub3d.h"

int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	put_pixel(t_data *data, int y, int x, int color)
{
	data->function_calls++;
	char	*offset;

	if (y < 0 || x < 0 || y > data->win_height || x > data->win_width)
		return ;
	offset = data->frame.addr + (y * data->frame.line_len + x
			* (data->frame.bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}

void	create_background(t_data *data)
{
	data->function_calls++;
	int	y;
	int	x;

	y = -1;
	while (++y < data->win_height)
	{
		x = -1;
		while (++x < data->win_width)
		{
			if (y > data->win_height / 2)
				put_pixel(data, y, x, data->color_floor);
			else
				put_pixel(data, y, x, data->color_ceiling);
		}
	}
}

void	debug(t_data *data)
{
	int time_since_start = get_time() - data->start;
	size_t func_calls = data->function_calls - 921600 - 921600;
	ft_printf("frame %d, time_since_start %d, function calls %zu\n", ++data->frame_count, time_since_start, func_calls);
	float res = data->frame_count / (time_since_start);
	ft_printf("fps %d\n", res);//!BAD
	// if (time_since_start > 250)
	// 	clean_exit(data, 0);
}

void	create_frame(t_data *data)
{
	data->function_calls++;
	create_background(data);
	raycast(data);
	if (data->map_active)
	create_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
	debug(data);
}
