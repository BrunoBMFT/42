/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2024/12/07 02:50:04 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
//check initialization of images and mlx before opening window

void	parser(int ac, char **av, t_data *data)
{
	name_check(ac, av);
	save_file(data, av[1]);
	save_texture_path(data);
	save_map(data);
	flood_fill(data);
	
	//at the end of everything parser, free file
}

int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	// print_file_info(&data);
	// print_map_info(&data);
	printf("all correct!\n");
	clean_everything(&data);
	return (0);
}
