#include "../includes/cub3d.h"

int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * img->bits_per_pixel);
	return (*(unsigned int *)dst);
}

void	put_pixel(t_data *data, int y, int x, int color)
{
	char	*offset;

	offset = data->frame.addr + (y * data->frame.line_len + x
			* data->frame.bits_per_pixel);
	*(unsigned int *)offset = color;
}


void	create_frame(t_data *data)
{
	++data->frame_count;
	raycast(data);
	// if (data->map_active)
	// 	create_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
}
