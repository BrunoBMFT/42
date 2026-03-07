#include "../includes/cub3d.h"

int	get_wall_height(t_data *data, float hyp, float angle)
{
	data->function_calls++;
	return ((SCALE * (data->win_width / 2) / tan(rad(FOV) / 2))
		/ (hyp * cos(rad(angle - data->p_angle))));
}

int	get_slice_texture(float x, float y, bool vert)
{
	if (vert)
		return (fmodf(y, SCALE) * TEXTURE_SIZE / SCALE);
	return (fmodf(x, SCALE) * TEXTURE_SIZE / SCALE);
}

int get_sprite_num(float player_x, float player_y, int x, int y, bool vert) {
	if (vert) {
		if (x > player_x)
			return (EAST);
		return (WEST);
	}
	if (y > player_y)
		return (SOUTH);
	return (NORTH);
}

void	draw_wall_section(t_data *data, int section, float angle, float hyp, float x, float y, bool vert)
{
	data->function_calls++;
	int		height;
	int		top, bot;
	float	tex_pos;
	int		tx, ty;

	height = get_wall_height(data, hyp, angle);
	top = (data->win_height / 2) - (height / 2);
	bot = (data->win_height / 2) + (height / 2);
	if (top < 0)
		top = 0;
	if (bot > data->win_height)
		bot = data->win_height;
	data->function_calls++;
	tx = get_slice_texture(x, y, vert);
	tex_pos = (top - data->win_height / 2 + height / 2)
		* (float)TEXTURE_SIZE / height;
	while (top < bot)
	{
		ty = tex_pos;
		if (ty >= TEXTURE_SIZE)
			ty = TEXTURE_SIZE - 1;
		data->function_calls++;
		int sprite_num = get_sprite_num(data->p_x, data->p_y, x, y, vert);
		data->function_calls++;
		int color = get_pixel(&data->sprites[sprite_num], tx, ty);
		put_pixel(data, top, section, color);
		tex_pos += (float)TEXTURE_SIZE / height;
		top++;
	}
}
