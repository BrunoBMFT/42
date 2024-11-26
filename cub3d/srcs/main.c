/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2024/11/26 01:49:48 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	save_texture_data(t_data *data)
{
	int i;

	i = 0;
	while (data->file[i])
	{
		if (ft_strncmp("NO", data->file[i], 2) == 0)
			data->tnorth = data->file[i] + 3;
		if (ft_strncmp("SO", data->file[i], 2) == 0)
			data->tsouth = data->file[i] + 3;
		if (ft_strncmp("WE", data->file[i], 2) == 0)
			data->twest = data->file[i] + 3;
		if (ft_strncmp("EA", data->file[i], 2) == 0)
			data->teast = data->file[i] + 3;
		i++;
	}
}

void	parser(int ac, char **av, t_data *data)
{
	name_check(ac, av);
	save_map(data, av[1]);
	save_texture_data(data);
}

int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	print_file_info(&data);
	clean_map(&data);
	return (0);
}
