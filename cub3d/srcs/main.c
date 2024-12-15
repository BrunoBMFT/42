/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2024/12/15 15:42:13 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
//decide if i do like it is now, or like so long (boolean returns)

void	init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error(data, "Mlx init failed");
	//have textures open and save into img here

	int x, y;
	mlx_get_screen_size(data->mlx, &x, &y);//check if it isnt too big
	data->win = mlx_new_window(data->mlx, x, y, "cub3d");
	if (!data->win)
		error(data, "Window failed to open");
}

void	add_coord(t_data *data, int y, int x)
{
	//need a img init, to save to the img the color
	//the img is what is gonna be each frame
	//i need to find color values for the minimap and decide where to put it
}

//need to find a way to only put it somewhere on the map
//also, want to find a simple way to change it position in the game
//   like having it at top right, bottom left
void	create_minimap(t_data *data)
{
	int y = 0;
	while (data->map[y])
	{
		int x = 0;
		while (data->map[y][x])
		{
			add_coord(data, y, x);//get a way to choose the color here
			x++;
		}
	}
}

int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	init(&data);

	create_minimap(&data);
	
	mlx_key_hook(data.win, handle_input, &data);
	mlx_hook(data.win, 17, 1L << 17, close_game, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
