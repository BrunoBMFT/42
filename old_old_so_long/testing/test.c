#include "so_long.h"

#define WIDTH	400
#define HEIGHT	400

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx_data;

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
	{
// if key press was Escape, it has to destroy both the window and the display, so no leaks from pressing escape
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free (data->mlx_ptr);
		exit(1);
	}
	printf("The %d key has been pressed\n\n", keysym);
	return (0);
}

int	main(void)
{
	t_mlx_data data;

// start connection with server
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
// open window
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "new window");
	if (!data.win_ptr)
	{
// destroys the display and frees pointer for no leaks
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}

// listens to the key presses, in this case, the handle_input function is, and quitting if key pressed was Escape
// printing which key was pressed
	mlx_key_hook(data.win_ptr, handle_input, &data);
	
// this makes it that the window stays open until forcibly closed (ctrl+c or Escape)
	mlx_loop(data.mlx_ptr);

// destroying the window and display closes the program and freeing makes sure no leaks are possible
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);//mem leak if ctrl+c
	mlx_destroy_display(data.mlx_ptr);

	free (data.mlx_ptr);
}