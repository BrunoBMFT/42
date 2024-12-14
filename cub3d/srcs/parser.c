/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:36:45 by bruno             #+#    #+#             */
/*   Updated: 2024/12/10 16:04:42 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_parser(t_data *data)
{
	data->file = NULL;
	data->map = NULL;
	data->visited = NULL;
	data->p_north = NULL;
	data->p_east = NULL;
	data->p_south = NULL;
	data->p_west = NULL;
	data->c_floor = NULL;
	data->c_ceiling = NULL;
}

void	name_check(int ac, char **av)
{
	int		len;
	char	*temp;

	if (ac != 2)
		error(NULL, "Wrong number of arguments");
	len = ft_strlen(av[1]);
	temp = av[1] + len - 4;
	if (len < 5 || ft_strcmp(temp, ".cub"))
		error(NULL, "Name is wrong");
}

bool	read_into_file(t_data *data, int fd, int loop)
{
	char	*map_line;

	map_line = get_next_line(fd);
	if (map_line)
		read_into_file(data, fd, loop + 1);
	else
	{
		data->file = ft_calloc(sizeof(char *), loop + 1);
		if (!data->file)
			error(NULL, "map calloc failed");
	}
	if (data->file)
	{
		data->file[loop] = ft_strtrim(map_line, "\n");
		return (free (map_line), true);
	}
	return (false);
}

void	save_file(t_data *data, char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		error(NULL, "fd failed to open");
	read_into_file(data, fd, 0);
	close (fd);
	if (!*data->file)
		error(data, "No file");
}

void	parser(int ac, char **av, t_data *data)
{
	init_parser(data);
	name_check(ac, av);
	save_file(data, av[1]);
	save_texture_path(data);
	save_map(data);
	flood_fill(data);
	
	//at the end of everything parser, free file
}
