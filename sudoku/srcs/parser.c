#include "../includes/sudoku.h"
//check for size
//check for big border
//check for small border
//check for impossible cases


bool	is_in_array(char *arr, char c)
{
	while (*arr)
	{
		if (c == *arr)
			return (true);
		arr++;
	}
	return (false);
}
//modify to accept new things
bool	check_char(t_map *map)
{
	int		y;
	int		x;

	y = -1;
	while (map->img[++y])
	{
		x = -1;
		while (map->img[y][++x])
		{
			if (!is_in_array(VALID, map->img[y][x]))
				return (ft_putendl(INV_CHAR), false);
		}
	}
	return (true);
}

bool	check_filename(char *file)
{
	int		len;
	char	*temp;

	temp = file;
	len = ft_strlen(file);
	temp = temp + len -4;
	if (len < 4 || ft_strncmp(temp, ".sdk", 4))
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
		map->img = ft_calloc((loop + 1), sizeof(char *));
	if (map->img)
	{
		map->img[loop] = ft_strtrim(line, "\n");
		free(line);
		return (true);
	}
	return (false);
}

bool	get_file(char *file, t_map *map)
{
	int		fd;
	char	*new;

	new = ft_strjoin("./sudokus/", file);
	fd = open(new, O_RDONLY);
	free (new);
	if (!read_file(map, fd, 0))
		return (close(fd), ft_putendl(ERR_FILE), false);
	close(fd);
	return (true);
}

bool	parser(int ac, char **av, t_map *map)
{
	if (!check_filename(av[1]))
		return (false);
	if (!get_file(av[1], map))
		return (false);
	return (true);
}
