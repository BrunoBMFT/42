#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIDE_LEN 800

// struct contains all image stuff that will buffer the pixels
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

// colors the pixel it receieves the coords of with the color, using alignment calculation
void	my_pixel_put(t_img * img, int x, int y, int color)
{
	int offset;
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));

// casts the pointer to an unsigned int, a pixel
	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}
// loops around the whole image to color all pixels using the function my_pixel_put
void	color_screen(t_data *data, int color)
{
	int	y = 0;
	while (y < SIDE_LEN)
	{
		int x = 0;
		while (x < SIDE_LEN)
		{
// the function is faster than the mlx library one
// buffers the image and pushes only when read, means no graphic flickers
			my_pixel_put(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}

int	f(int keysym, t_data *data)
{	
	if (keysym == XK_r)
		color_screen(data, 0xff0000);
	else if (keysym == XK_g)
		color_screen(data, 0xff00);
	else if (keysym == XK_b)
		color_screen(data, 0xff);
	else if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free (data->mlx);
		exit(1);
	}

// puts the ready image to the window
// last params are the offest image-window (????)
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	return (0);
}
// my own function so no clogging
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

// gets pointer to the image
	vars.img.img_ptr = mlx_new_image(vars.mlx, SIDE_LEN, SIDE_LEN);
	if (!vars.img.img_ptr)
		return (free_windows(&vars));

// pointer to first pixel
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