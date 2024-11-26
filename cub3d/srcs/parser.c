/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:36:45 by bruno             #+#    #+#             */
/*   Updated: 2024/11/26 01:49:06 by bruno            ###   ########.fr       */
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
		data->file = ft_calloc(sizeof(char *), loop + 1);
		if (!data->file)
			error("map calloc failed");
	}
	if (data->file)
	{
		data->file[loop] = ft_strtrim(map_line, "\n");
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

void print_file_info(t_data *data)
{
	int i = 0;
	while (data->file[i])
	{
		printf("%s\n", data->file[i]);
		i++;
	}
	printf("%s\n%s\n%s\n%s\n", data->tnorth, data->tsouth, data->twest, data->teast);
}

void print_map_info(t_data *data)
{
	int i = 0;
	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
}
