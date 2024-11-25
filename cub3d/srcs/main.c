/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:51:28 by bruno             #+#    #+#             */
/*   Updated: 2024/11/25 00:09:44 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	name_check(int ac, char **av)
{
	int		len;
	char	*temp;

	if (ac != 2)
		error("Wrong number of arguments");
	len = ft_strlen(av[1]);
	temp = av[1] + len - 4;
	if (len < 5 || ft_strcmp(temp, ".cub"))
		error("Name is wrong");
}

bool	read_into_map(t_data *data, int fd, int loop)
{
	char	*map_line;

	map_line = get_next_line(fd);
	if (map_line)//recursive part
		read_into_map(data, fd, loop + 1);
	else
	{
		data->map = ft_calloc(sizeof(char *), loop + 1);
		if (!data->map)
			error("map calloc failed");
	}
	if (data->map)
	{
		data->map[loop] = ft_strtrim(map_line, "\n");
		return (free (map_line), true);
	}
	return (false);
}

void	save_map(t_data *data, char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		error("fd failed to open");
	read_into_map(data, fd, 0);
}

void	parser(int ac, char **av, t_data *data)
{
	name_check(ac, av);
	save_map(data, av[1]);
	int i = 0;
	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data data;
	parser(ac, av, &data);
	printf("playable map\n");
	return (0);
}
