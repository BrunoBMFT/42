/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/05/03 16:27:44 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (!init(ac, av, &data))
		return (clean_everything(&data), 1);
	// create_frame(&data);
	mlx_key_hook(data.win, input, &data);
	//have a on_press and a on_release
	mlx_hook(data.win, 17, 1L << 17, clean_exit, &data);
	mlx_loop_hook(data.mlx, create_frame, &data);
	printf("all ok\n");
	mlx_loop(data.mlx);
	return (0);
}
