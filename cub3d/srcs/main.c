/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2024/11/30 19:58:26 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	char_allowed(char *str)//not working too well
{
	int i = 0;

	while (str[i])
	{
		if (!ft_strchr(POSSIBLE, str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	save_map(t_data *data)
{
	int i = 0;
	int count = 0;
	while (data->file[i])
	{
		if (char_allowed(data->file[i]))
		{
			count++;
		}
		i++;
	}
	printf("count: %d\n", count);
}

void	parser(int ac, char **av, t_data *data)
{
	name_check(ac, av);
	save_file(data, av[1]);
	save_texture_path(data);
	save_map(data);
}

int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	print_file(&data);
//	print_file_info(&data);
	clean_everything(&data);
	return (0);
}
