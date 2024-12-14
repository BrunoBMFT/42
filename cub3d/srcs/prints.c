/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:38:36 by bruno             #+#    #+#             */
/*   Updated: 2024/12/14 02:46:18 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	print_textures(t_data *data)
{
	printf("paths:\n");
	printf("north:   %s\n", data->p_north);
	printf("east:    %s\n", data->p_east);
	printf("south:   %s\n", data->p_south);
	printf("west:    %s\n", data->p_west);
	printf("colors:\n");
	printf("floor:   %s\n", data->c_floor);
	printf("ceiling: %s\n", data->c_ceiling);
}

void	print_file_info(t_data *data)
{
	print_array(data->parser->file);
	printf("\n\nPROCESSED INFO\n\n");
	print_textures(data);
	printf("\nmap:\n");
	print_array(data->map);
	printf("\n\n");
}

void	print_map_info(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
}
