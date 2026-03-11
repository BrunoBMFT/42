#include "../includes/cub3d.h"

bool	init_texture_img(t_data *data, t_img *texture, char *img_src)
{
	texture->img = NULL;
	texture->img = mlx_xpm_file_to_image(data->mlx,
			img_src, &texture->width, &texture->height);
	if (!texture->img)
		return (error("A image failed to initialize"));
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_len, &texture->endian);
	texture->bits_per_pixel /= 8;
	if (!texture->addr)
		return (error("An image address failed to initialize"));
	return (true);
}

bool	init_imgs(t_data *data)
{
	if (!init_texture_img(data, &data->sprites[NORTH], data->paths[NORTH])
		|| !init_texture_img(data, &data->sprites[EAST], data->paths[EAST])
		|| !init_texture_img(data, &data->sprites[SOUTH], data->paths[SOUTH])
		|| !init_texture_img(data, &data->sprites[WEST], data->paths[WEST]))
		return (false);
	data->frame.img = mlx_new_image(data->mlx,
			data->win_width, data->win_height);
	if (!data->frame.img)
		return (error("Frame failed to initialize"));
	data->frame.addr = mlx_get_data_addr(data->frame.img,
			&data->frame.bits_per_pixel,
			&data->frame.line_len, &data->frame.endian);
	data->frame.bits_per_pixel /= 8;
	if (!data->frame.addr)
		return (error("Frame address failed to initialize"));
	return (true);
}

void	player_angle_init(t_data *data, int facing)
{
	if (facing == 'N')
		data->p_angle = 0;
	else if (facing == 'E')
		data->p_angle = 90;
	else if (facing == 'S')
		data->p_angle = 180;
	else if (facing == 'W')
		data->p_angle = 270;
}

bool	player_init(t_data *data)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NESW", data->map[y][x]))
			{
				data->p_y = y * SCALE;
				data->p_x = x * SCALE;
				count++;
				player_angle_init(data, data->map[y][x]);
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (error("Invalid player"));
	return (true);
}
