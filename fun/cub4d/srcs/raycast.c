#include "../includes/cub3d.h"

bool	hit_inter(t_data *data, float y, float x)
{
	data->function_calls++;
	size_t	map_y;
	size_t	map_x;

	map_x = floor(x / SCALE);
	map_y = floor(y / SCALE);
	if (map_y >= data->map_height
		|| map_x >= ft_strlen(data->map[map_y]))
		return (false);
	if (data->map[map_y][map_x] == '1')
		return (false);
	return (true);
}

float	inter_h_step(t_data *data, float angle, float *x, float *y)
{
	data->function_calls++;
	int		x_dir;
	float	y_step;
	float	x_step;

	data->function_calls++;
	angle_correct(&angle, &x_dir, true);
	*x = floor(data->p_x / SCALE) * SCALE;
	if (x_dir == 1)
		*x += SCALE;
	else
		*x -= 0.0001f;
	*y = data->p_y + (*x - data->p_x) / tan(rad(angle));
	x_step = SCALE * x_dir;
	y_step = x_step / tan(rad(angle));
	while (hit_inter(data, *y, *x))
	{
		*y += y_step;
		*x += x_step;
	}
	return (sqrt(pow(data->p_y - *y, 2) + pow(data->p_x - *x, 2)));
}

float	inter_v_step(t_data *data, float angle, float *x, float *y)
{
	data->function_calls++;
	int		y_dir;
	float	y_step;
	float	x_step;

	data->function_calls++;
	angle_correct(&angle, &y_dir, false);
	*y = floor(data->p_y / SCALE) * SCALE;
	if (y_dir == 1)
		*y += SCALE;
	else
		*y -= 0.0001f;
	*x = data->p_x + (*y - data->p_y) * tan(rad(angle));
	y_step = SCALE * y_dir;
	x_step = y_step * tan(rad(angle));
	while (hit_inter(data, *y, *x))
	{
		*y += y_step;
		*x += x_step;
	}
	return (sqrt(pow(data->p_y - *y, 2) + pow(data->p_x - *x, 2)));
}

int		get_smallest_distance(float hyp1, float hyp2) {
	if (hyp1 < hyp2)
		return (0);
	return (1);
}

void	raycast(t_data *data)
{
	data->function_calls++;
	int		section;
	float	angle;
	float	hyp[2];
	int		flag;//horrible name
	float	x[2], y[2];

	angle = data->p_angle - FOV / 2;
	section = 0;
	while (section < data->win_width)
	{
		hyp[0] = inter_v_step(data, angle, &x[0], &y[0]);
		hyp[1] = inter_h_step(data, angle, &x[1], &y[1]);
		data->function_calls++;
		flag = get_smallest_distance(hyp[0], hyp[1]);
		draw_wall_section(data, section, angle, hyp[flag], 
			x[flag], y[flag], flag);
		angle = angle + (FOV * 0.00078125);
		section++;
	}
}
