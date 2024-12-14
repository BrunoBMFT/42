/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2024/12/10 15:49:48 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
//check initialization of images and mlx before opening window

//test if parser frees everything in every case
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
