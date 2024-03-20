#include "minilibx-linux/mlx.h"
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH	400
#define HEIGHT	400

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_data;


int	button_press(int button, int x, int y, t_data *data)
{
	if (button == 1)
		printf("Left mouse button pressed at (%d, %d)\n", x, y);
	else if (button == 3)
		printf("Right mouse button pressed at (%d, %d)\n", x, y);
	return (0);
}

int	main(void)
{
	t_data data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "new window");
	if (!data.win_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}

// mlx_hook listens to mouse inputs (moving, left click and right click)
// Events (like ButtonPress) describes when the mouse is pressed or moved
// Event Masks (like ButtonPressMask) filter the events the program listens for (like saying: notify me when this event happens)
	mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, &button_press, &data);
	
	mlx_loop(data.mlx_ptr);

	mlx_destroy_window(data.mlx_ptr, data.win_ptr);//mem leak if ctrl+c
	mlx_destroy_display(data.mlx_ptr);

	free (data.mlx_ptr);
}