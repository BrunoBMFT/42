#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		color;
}				t_data;

int	f(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free (data->mlx);
		exit(1);
	}
	printf("Pressed %d\n", keysym);
	sleep(1);
	return (1);
}

int	change_color(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 150, 150, data->color, "Color changing window");
	
//it's gonna cycle through colors as long as no event is happening
	if (data->color == 0xFF0000)
		data->color = 0x00FF00;
	else if (data->color == 0x00FF00)
		data->color = 0x0000FF;
	else
		data->color = 0xFF0000;
	return (0);
}

int	main(void)
{
	t_data data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, 400, 400, "new window");
	if (!data.win)
	{
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (1);
	}
	data.color = 0xFF0000; //red

	mlx_key_hook(data.win, f, &data);

// this hook is triggered when there's no event processed
// continuous screen rendering since nothing is being pressed or moved
	mlx_loop_hook(data.mlx, change_color, &data);

	mlx_loop(data.mlx);

	mlx_destroy_window(data.mlx, data.win);//mem leak if ctrl+c
	mlx_destroy_display(data.mlx);

	free (data.mlx);
}