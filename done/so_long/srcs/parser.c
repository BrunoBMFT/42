/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 04:33:45 by bruno             #+#    #+#             */
/*   Updated: 2024/05/16 12:12:33 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

bool	check_filename(char *file)
{
	int		len;
	char	*temp;

	temp = file;
	len = ft_strlen(file);
	temp = temp + len -4;
	if (len < 4 || ft_strncmp(temp, ".ber", 4))
		return (ft_putendl(INV_MAPNAME), false);
	return (true);
}

bool	read_file(t_map *map, int fd, int loop)
{
	char	*line;

	line = get_next_line(fd);
	if (line)
	{
		if (!read_file(map, fd, loop + 1))
			return (false);
	}
	else
	{
		map->map = ft_calloc((loop + 1), sizeof(char *));
		if (!map->map)
			return (false);
	}
	if (map->map)
	{
		map->map[loop] = ft_strtrim(line, "\n");
		free(line);
		return (true);
	}
	return (false);
}

bool	get_file(char *file, t_map *map)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putendl(INV_FILE), false);
	if (!read_file(map, fd, 0))
		return (close(fd), ft_putendl(ERR_FILE), false);
	close(fd);
	return (true);
}

bool	parser(int ac, char **av, t_map *map)
{
	if (ac != 2)
		return (ft_putendl(INV_ARGS), false);
	if (!check_filename(av[1]))
		return (false);
	if (!get_file(av[1], map))
		return (false);
	if (!validate_map(map))
		return (false);
	return (true);
}
