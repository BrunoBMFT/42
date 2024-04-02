/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:45:17 by bruno             #+#    #+#             */
/*   Updated: 2024/04/02 16:33:04 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define SIDE_LEN 600

typedef struct s_data
{
	void	*mlx;
	void	*win;
}				t_data;

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

/*int	main(int ac, char **av)
{
	t_map	map;

	init(&map);
	//need to make a check for exit and if all C are collectible
	//need to make check if game is rectangular
	//need to check if player is inbounds (caught in flood)
	if (!parser(ac, av, &map))
		return (ft_printf("failed successfully"), free_parser(&map), 1);
	else
		printf("ran without problems");
	free_parser(&map);
}*/


int	main(void)
{
	t_data vars;
//	void	*img;
//	char	*path = "./amogus.xpm";
//	int		img_width;
//	int		img_height;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);
	vars.win = mlx_new_window(vars.mlx, SIDE_LEN, SIDE_LEN, "new window");
	if (!vars.win)
		return (free_windows(&vars));

//	img = mlx_xpm_file_to_image(vars.mlx, path, &img_width, &img_height);

//	mlx_put_image_to_window(vars.mlx, vars.win, img, 0, 0);

	mlx_key_hook(vars.win, f, &vars);

	mlx_loop(vars.mlx);//quit using esc, still mem leaks, probably not freeing img.img_ptr and img.img_pixels_ptr

	free (vars.mlx);
}