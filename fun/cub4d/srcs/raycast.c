#include "../includes/cub3d.h"

bool	hit_inter(t_data *data, double y, double x)//rename, cause it should return true if it hits
{
	size_t	map_y;
	size_t	map_x;

	map_x = (int)x / SCALE;
	map_y = (int)y / SCALE;
	if (map_y >= data->map_height
		|| map_x >= ft_strlen(data->map[map_y]))//remove ft_strlen, replace for row_len
		return (false);//this whole check is useless
	if (data->map[map_y][map_x] == '1')
		return (false);
	return (true);
}

double	inter_h_step(t_data *data, t_ray *ray, double angle, double *x, double *y)
{
	int		x_dir;
	double	y_step;
	double	x_step;

	angle_correct(&angle, &x_dir, true);
	*x = (floor(ray->player_x / SCALE)) * SCALE;
	if (x_dir == 1)
		*x += SCALE;
	else
		*x -= 0.0001f;
	*y = ray->player_y + (*x - ray->player_x) / tan(rad(angle));
	x_step = SCALE * x_dir;
	y_step = x_step / tan(rad(angle));
	while (hit_inter(data, *y, *x))
	{
		*y += y_step;
		*x += x_step;
	}
	return (sqrt(pow(data->p_y - *y, 2) + pow(data->p_x - *x, 2)));
}

double	inter_v_step(t_data *data, t_ray *ray, double angle, double *x, double *y)
{
	int		y_dir;
	double	y_step;
	double	x_step;
	
	angle_correct(&angle, &y_dir, false);
	*y = floor(ray->player_y / SCALE) * SCALE;
	if (y_dir == 1)
		*y += SCALE;
	else
		*y -= 0.0001f;
	*x = ray->player_x + (*y - ray->player_y) * tan(rad(angle));
	y_step = SCALE * y_dir;
	x_step = y_step * tan(rad(angle));
	while (hit_inter(data, *y, *x))
	{
		*y += y_step;
		*x += x_step;
	}
	double dx = data->p_x - *x, dy = ray->player_y - *y;
	return (sqrt(dx*dx + dy*dy));
}

void	init_ray(t_data *data, t_ray *ray)
{
	ray->player_x = data->p_x;
	ray->player_y = data->p_y;
	ray->hit = false;
	ray->angle = data->p_angle - FOV / 2;
	ray->hit_v_x = 0;
	ray->hit_v_y = 0;
	ray->hit_h_x = 0;
	ray->hit_h_y = 0;
	ray->distance_v = 0;
	ray->distance_h = 0;
}

void	raycast(t_data *data)
{
	t_ray ray;
	int section = 0;
	init_ray(data, &ray);

	while (section < WIN_WIDTH)
	{
		ray.tan_a = tan(rad(ray.angle));
		ray.distance_h = inter_h_step(data, &ray, ray.angle, &ray.hit_h_x, &ray.hit_h_y);
		ray.distance_v = inter_v_step(data, &ray, ray.angle, &ray.hit_v_x, &ray.hit_v_y);
		if (ray.distance_h < ray.distance_v)
			draw_wall_section(data, section, ray.angle, ray.distance_h, ray.hit_h_x, ray.hit_h_y, 1);
		else 
			draw_wall_section(data, section, ray.angle, ray.distance_v, ray.hit_v_x, ray.hit_v_y, 0);
		ray.angle += (FOV * 0.00078125);//stupid
		section++;
	}
}
