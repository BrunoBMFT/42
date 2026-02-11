/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:36:45 by brfernan          #+#    #+#             */
/*   Updated: 2025/05/12 15:01:57 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
		return (error("Nothing in file"));
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
	return (true);
}
