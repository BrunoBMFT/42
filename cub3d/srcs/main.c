/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2024/12/15 13:34:05 by bruno            ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	init(&data);



	
	printf("all ok\n");
	mlx_key_hook(data.win, handle_input, &data);
	mlx_hook(data.win, 17, 1L << 17, close_game, &data);
	mlx_loop(data.mlx);
	return (0);
}
