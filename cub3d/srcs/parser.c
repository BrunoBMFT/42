/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:36:45 by bruno             #+#    #+#             */
/*   Updated: 2024/12/20 10:53:29 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_parser(t_data *data)
{
	data->file = NULL;
	data->visited = NULL;
	data->map = NULL;
	data->p_north = NULL;
	data->p_east = NULL;
	data->p_south = NULL;
	data->p_west = NULL;
	data->c_floor = NULL;
	data->c_ceiling = NULL;
	
	data->texture = NULL;
	data->mlx = NULL;
	data->win = NULL;
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
		error(NULL, "File not found");
	read_into_file(data, fd, 0);
	close (fd);
	if (!*data->file)
		error(data, "No file");
}

void	check_paths(t_data *data)
{
	if (access(data->p_north, R_OK))
		error(data, "North texture not found");
	if (access(data->p_east, R_OK))
		error(data, "East texture not found");
	if (access(data->p_south, R_OK))
		error(data, "South texture not found");
	if (access(data->p_west, R_OK))
		error(data, "West texture not found");
}

void	save_texture_path(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->file[i])
	{
		temp = data->file[i];
		if (ft_strncmp("NO", temp, 2) == 0)
			data->p_north = ft_strdup(temp + 3);
		if (ft_strncmp("EA", temp, 2) == 0)
			data->p_east = ft_strdup(temp + 3);
		if (ft_strncmp("SO", temp, 2) == 0)
			data->p_south = ft_strdup(temp + 3);
		if (ft_strncmp("WE", temp, 2) == 0)
			data->p_west = ft_strdup(temp + 3);
		if (ft_strncmp("F", temp, 1) == 0)
			data->c_floor = ft_strdup(temp + 2);
		if (ft_strncmp("C", temp, 1) == 0)
			data->c_ceiling = ft_strdup(temp + 2);
		i++;
	}
	if (!data->p_north || !data->p_east || !data->p_south
		|| !data->p_west)
		error(data, "Missing paths");
	if (!data->c_floor || !data->c_ceiling)
		error(data, "Missing colors");
	check_paths(data);
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
