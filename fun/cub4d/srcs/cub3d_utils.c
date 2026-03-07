#include "../includes/cub3d.h"

bool	error(char *str)
{
	ft_printf_fd(2, "Error!\n%s\n", str);
	return (false);
}

void	my_free(void *ptr) {
	if (ptr)
		free (ptr);
}

void	my_destroy_image(void *mlx_ptr, void *img_ptr)
{
	if (img_ptr)
		mlx_destroy_image(mlx_ptr, img_ptr);
}

void	clean_texture_path(t_data *data)
{
	my_free(data->paths[NORTH]);
	my_free(data->paths[EAST]);
	my_free(data->paths[SOUTH]);
	my_free(data->paths[WEST]);
	my_free(data->paths[FLOOR]);
	my_free(data->paths[CEILING]);
}

void	clean_imgs(t_data *data)
{
	my_destroy_image(data->mlx, data->sprites[NORTH].img);
	my_destroy_image(data->mlx, data->sprites[EAST].img);
	my_destroy_image(data->mlx, data->sprites[SOUTH].img);
	my_destroy_image(data->mlx, data->sprites[WEST].img);
}

void	clean_exit(t_data *data, int exit_code)
{
	if (!data)
		return ;
	if (data->file)
		free_array(data->file);
	if (data->map)
		free_array(data->map);
	clean_imgs(data);
	my_destroy_image(data->mlx, data->frame.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	clean_texture_path(data);
	exit(exit_code);
}

int	mlx_clean_exit(t_data *data)
{
	clean_exit(data, 0);
	return (0);
}
