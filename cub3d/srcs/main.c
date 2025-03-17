/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2025/03/17 21:39:02 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_data data;
	if (!parser(ac, av, &data))
		return (clean_everything(&data), 1);


	//*fixed values for window size
	//init mlx
	//init textures and check
	//init window
	//test if textures work
	//start rays
	clean_everything(&data);
	printf("all ok\n");
	return (0);
}
