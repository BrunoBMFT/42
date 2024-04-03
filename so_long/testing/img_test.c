#include "so_long.h"

int	f(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free (data->mlx);
		exit(1);
	}
	return (0);
}
int	free_windows(t_data *vars)
{
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	return (1);
}

int	main(void)
{
	t_data vars;
	void	*img;
	char	*path = "./amogus.xpm";
	int		img_width;
	int		img_height;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);
	vars.win = mlx_new_window(vars.mlx, SIDE_LEN, SIDE_LEN, "new window");
	if (!vars.win)
		return (free_windows(&vars));

	img = mlx_xpm_file_to_image(vars.mlx, path, &img_width, &img_height);

	mlx_put_image_to_window(vars.mlx, vars.win, img, 0, 0);

	mlx_key_hook(vars.win, f, &vars);

	mlx_loop(vars.mlx);//quit using esc, still mem leaks, probably not freeing img.img_ptr and img.img_pixels_ptr

	free (vars.mlx);
}