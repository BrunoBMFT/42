/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:36:45 by bruno             #+#    #+#             */
/*   Updated: 2025/04/07 02:28:34 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	name_check(int ac, char **av)
{
	int		len;
	char	*temp;

	if (ac != 2)
		return (error("Wrong number of arguments"));
	len = ft_strlen(av[1]);
	temp = av[1] + len - 4;
	if (len < 5 || ft_strcmp(temp, ".cub"))
		return (error("Name is wrong"));
	return (true);
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
			return (error("map calloc failed"));
	}
	if (data->file)
	{
		data->file[loop] = ft_strtrim(map_line, "\n");
		return (free (map_line), true);
	}
	return (true);
}

bool	save_file(t_data *data, char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (error("File not found"));
	read_into_file(data, fd, 0);
	close (fd);
	if (!*data->file)
		return (error("No file"));
	return (true);
}

bool	check_paths(t_data *data)
{
	if (access(data->p_north, R_OK) || access(data->p_east, R_OK)
		|| access(data->p_south, R_OK) || access(data->p_west, R_OK))
		return (error("missing texture"));
	return (true);
}

bool	path_already_saved(t_data *data, char *temp)
{
	if ((!ft_strncmp("NO", temp, 2) && data->p_north)
		|| (!ft_strncmp("EA", temp, 2) && data->p_east)
		|| (!ft_strncmp("SO", temp, 2) && data->p_south)
		|| (!ft_strncmp("WE", temp, 2) && data->p_west)
		|| (!ft_strncmp("F", temp, 1) && data->p_floor)
		|| (!ft_strncmp("C", temp, 1) && data->p_ceiling))
		return (true);
	return (false);
}

bool	texture_char_check(char *color)// TODO check limits and commas
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_strchr("0123456789,", color[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	texture_check(t_data *data)
{
	int	i;

	if (!data->p_north || !data->p_east || !data->p_south
		|| !data->p_west || !data->p_floor || !data->p_ceiling)
		return (error("Missing info"));
	if (!*data->p_ceiling || !*data->p_floor)
		return (error("Missing info"));
	if (!texture_char_check(data->p_ceiling)
		|| !texture_char_check(data->p_floor))
		return (error("Invalid colors"));
	return (true);
}

bool	save_texture_path(t_data *data)
{
	int		i;

	i = 0;
	while (data->file[i])
	{
		if (path_already_saved(data, data->file[i]))
			return (error("Duplicate paths"));
		if (!ft_strncmp("NO", data->file[i], 2))
			data->p_north = ft_strtrim(data->file[i] + 2, " \t");
		else if (!ft_strncmp("EA", data->file[i], 2))
			data->p_east = ft_strtrim(data->file[i] + 2, " \t");
		else if (!ft_strncmp("SO", data->file[i], 2))
			data->p_south = ft_strtrim(data->file[i] + 2, " \t");
		else if (!ft_strncmp("WE", data->file[i], 2))
			data->p_west = ft_strtrim(data->file[i] + 2, " \t");
		else if (!ft_strncmp("F", data->file[i], 1))
			data->p_floor = ft_strtrim(data->file[i] + 1, " \t");
		else if (!ft_strncmp("C", data->file[i], 1))
			data->p_ceiling = ft_strtrim(data->file[i] + 1, " \t");
		i++;
	}
	return (true);
}

void	player_angle_init(t_data *data, int facing)
{
	if (facing == 'N')
		data->p_angle = 0;
	else if (facing == 'E')
		data->p_angle = 90;
	else if (facing == 'S')
		data->p_angle = 180;
	else if (facing == 'W')
		data->p_angle = 270;
	data->door_opened = false;
}

bool	player_init(t_data *data)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NESW", data->map[y][x]))
			{
				data->p_y = y * SCALE;
				data->p_x = x * SCALE;
				player_angle_init(data, data->map[y][x]);
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (error("Invalid player"));
	return (true);
}

bool	parser(int ac, char **av, t_data *data)
{
	if (!name_check(ac, av))
		return (false);
	if (!save_file(data, av[1]))
		return (false);
	if (!save_texture_path(data))
		return (false);
	if (!texture_check(data))
		return (false);
	if (!save_map(data))
		return (false);
	if (!map_check(data))
		return (false);
	if (!player_init(data))
		return (false);
	return (true);
}
