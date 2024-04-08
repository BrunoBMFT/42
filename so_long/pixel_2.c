
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
#include <X11/X.h>
# include <unistd.h>
# include <stdio.h>//remove
# include <stdlib.h>
# include <stdbool.h>
# include <stdarg.h>
# include <fcntl.h>
#define SIDE_LEN 600

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

int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;
	dst = img->img_ptr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int offset;
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));

	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

void	put_image_to_window(t_img *img, t_img src)
{
	int color;
	int	y = 0;
	while (y < SIDE_LEN)
	{
		int x = 0;

			while (x < SIDE_LEN)
			{
//				color = get_pixel(&src, x, y);
				my_pixel_put(img, x, y, 0x0000FF);
				x++;
			}
		y++;
	}
}

int	f(int keysym, t_data *data)
{
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




	void	*img;
	char	*path = "./amogus.xpm";
	int		img_width;
	int		img_height;
	vars.img.img_ptr = mlx_xpm_file_to_image(vars.mlx, path, &img_width, &img_height);


	vars.img.img_pixels_ptr = mlx_get_data_addr(vars.img.img_ptr, &vars.img.bits_per_pixel, 
												&vars.img.line_len, &vars.img.endian);
	if (!vars.img.img_pixels_ptr)
		return (free_windows(&vars));


	put_image_to_window(img, vars.img);



	mlx_key_hook(vars.win, f, &vars);

	mlx_loop(vars.mlx);//quit using esc, still mem leaks, probably not freeing img.img_ptr and img.img_pixels_ptr

	free (vars.mlx);
}