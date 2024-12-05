/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2024/12/03 18:00:32 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parser(int ac, char **av, t_data *data)
{
	name_check(ac, av);
	save_file(data, av[1]);
	save_texture_path(data);
	save_map(data);

	
	//at the end of everything parser, free file
}

int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	// print_file_info(&data);
	print_map_info(&data);
	clean_everything(&data);
	return (0);
}
