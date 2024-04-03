#include "so_long.h"

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}				t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
}				t_data;

void	my_pixel_put(t_img * img, int x, int y, int color)
{
	int offset;
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));

	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}


void	color_screen(t_data *data, int color)
{
	int	y = 0;
	while (y < SIDE_LEN)
	{
		int x = 0;

		if (y == 0 || y == SIDE_LEN - 1)
		{
			while (x < SIDE_LEN)
			{
				my_pixel_put(&data->img, x, y, 0x00FF00);
				x++;
			}
		}
		else
		{
			while (x < SIDE_LEN)
			{
				if (x == 0 || x == SIDE_LEN - 1)
					my_pixel_put(&data->img, x, y, 0x00FF00);
				else
					my_pixel_put(&data->img, x, y, color);
				x++;
			}
		}
		y++;
	}
}

int	f(int keysym, t_data *data)
{	
	color_screen(data, 0x000000);
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free (data->mlx);
		exit(1);
	}

	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
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

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);
	vars.win = mlx_new_window(vars.mlx, SIDE_LEN, SIDE_LEN, "new window");
	if (!vars.win)
		return (free_windows(&vars));


	vars.img.img_ptr = mlx_new_image(vars.mlx, SIDE_LEN, SIDE_LEN);
	if (!vars.img.img_ptr)
		return (free_windows(&vars));

	vars.img.img_pixels_ptr = mlx_get_data_addr(vars.img.img_ptr, &vars.img.bits_per_pixel, 
												&vars.img.line_len, &vars.img.endian);
	if (!vars.img.img_pixels_ptr)
		return (free_windows(&vars));
												

	printf("Line_len %d <-> Side_len %d\nbits per pixel %d\nendian %d\n", 
			vars.img.line_len, SIDE_LEN, vars.img.bits_per_pixel, vars.img.endian);

	mlx_key_hook(vars.win, f, &vars);

	mlx_loop(vars.mlx);//quit using esc, still mem leaks, probably not freeing img.img_ptr and img.img_pixels_ptr

	free (vars.mlx);
}