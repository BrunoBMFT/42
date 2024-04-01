/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:45:17 by bruno             #+#    #+#             */
/*   Updated: 2024/04/02 00:05:09 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init(t_map *map)
{
	map->map = NULL;
	map->visited = NULL;
}

void	free_file(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_parser(t_map *map)
{
	if (map->map)
		free_file(map->map);
	if (map->visited)
		free_file((char **)map->visited);
}

bool	check_filename(char *file)
{
	int	len;

	len = ft_strlen(file);
	file = file + len -4;
	if (len < 4 || ft_strncmp(file, ".ber", 4))
		return (false);//putendl com flags criadas pelo fontao
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
		map->map = ft_calloc((loop + 1), sizeof(char *));//map->buffer
		if (!map->map)//map->buffer
			return (false);
	}
	if (map->map)//map->buffer
	{
		map->map[loop] = ft_strtrim(line, "\n");//not sure if use strtrim
		free(line);
		return (true);
	}
	return (false);
}

bool	get_file(char *file, t_map *map)
{
	int		fd;
	char	*new;

	new = ft_strjoin("maps/", file);
	if (!new)
		return (false);//putendl com flags criadas pelo fontao
	fd = open(new, O_RDONLY);
	free (new);
	if (fd == -1)
		return (false);//putendl com flags criadas pelo fontao
	if (!read_file(map, fd, 0))
		return (close(fd), false);//putendl com flags criadas pelo fontao
	close(fd);
	return (true);
}

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

bool	check_char(t_map *map)
{
	int		y;
	int		x;
	int		player;

	player = 0;
	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (!is_in_array(VALID, map->map[y][x]))
				return (false);//putendl com flags criadas pelo fontao
			if (is_in_array("P", map->map[y][x]))//DEFINE PLAYER
				player++;
			if (player > 1)
				return (false);//putendl com flags criadas pelo fontao
			x++;
		}
		y++;
	}
	if (player == 0)
		return (false);//putendl com flags criadas pelo fontao
	return (true);
}

void	set_visitied(t_map *map)//get col and row as parameter
{
	int	col;
	int	row;

	col = 0;
	while (map->map[col])
	{
		row = 0;
		while (map->map[col][row])
		{
			map->visited[col][row] = false;
			row++;
		}
		col++;
	}
}

bool	initiate_flood(t_map *map)
{
	int	col;
	int	row;

	col = 0;
	while (map->map[col])
		col++;
	map->visited = ft_calloc(sizeof(bool *), col + 1);
	if (!map->visited)
		return (false);//putendl com flags criadas pelo fontao
	col--;
	while (col >= 0)
	{
		row = 0;
		while (map->map[col][row])
			row++;
		map->visited[col] = malloc(row * sizeof(bool));//change to ft_calloc
		if (!map->visited[col])
			return (false);//putendl com flags criadas pelo fontao
		col--;
	}
	set_visitied(map);
	return (true);
}

bool	flood_fill(t_map *map, int col, int row)
{
	if (col < 0 || row < 0 || !map->map[col]
		|| row >= (int)ft_strlen(map->map[col]))
		return (false);
	if (map->map[col][row] == '1' || map->visited[col][row])
		return (true);
	map->visited[col][row] = true;
	if (!flood_fill(map, col + 1, row))
		return (false);
	if (!flood_fill(map, col - 1, row))
		return (false);
	if (!flood_fill(map, col, row + 1))
		return (false);
	if (!flood_fill(map, col, row - 1))
		return (false);
	return (true);
}

bool	check_surroundings(t_map *map)//get col and row as parameter?
{
	int	col;
	int	row;

	col = 0;
	while (map->map[col])
	{
		row++;
		while (map->map[col][row])
		{
			if ((map->map[col][row] || is_in_array("P", map->map[col][row]))
			&& map->visited[col][row] == false)
			{
				if (!flood_fill(map, col, row))
					return (false);//putendl com flags criadas pelo fontao
			}
			row++;
		}
		col++;
	}
	return (true);
}

bool	validate_map(t_map *map)
{
	if (!check_char(map))
		return (false);
	if (!initiate_flood(map))
		return (false);
	if (!check_surroundings(map))
		return (false);
	return (true);
}

bool	parser(int ac, char **av, t_map *map)
{
	if (ac != 2)
		return (false);//putendl com flags criadas pelo fontao
	if (!check_filename(av[1]))
		return (false);
	if (!get_file(av[1], map))// ! not working
		return (false);
//	if (!get_args(map))//not needed
//		return (false);
//	if (!validate_map(map))
//		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_map	map;

	init(&map);
	if (!parser(ac, av, &map))
		return (free_parser(&map), 1);
	else
		printf("ran without problems");
	free_parser(&map);
}
