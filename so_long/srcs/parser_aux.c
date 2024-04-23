/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:24:20 by bruno             #+#    #+#             */
/*   Updated: 2024/04/23 18:37:12 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

bool	check_char_aux(t_map *map, int x, int y)
{
	if (!is_in_array(VALID, map->map[y][x]))
		return (ft_putendl(INV_CHAR), false);
	if (is_in_array("P", map->map[y][x]))
		map->numplayer++;
	if (is_in_array("E", map->map[y][x]))
		map->numexit++;
	if (is_in_array("C", map->map[y][x]))
		map->numcollectible++;
	return (true);
}

bool	check_char(t_map *map)
{
	int		y;
	int		x;

	map->numplayer = 0;
	map->numexit = 0;
	map->numcollectible = 0;
	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (!check_char_aux(map, x, y))
				return (false);
			x++;
		}
		y++;
	}
	if (map->numplayer == 0 || map->numexit == 0 || map->numplayer > 1
		|| map->numexit > 1 || map->numcollectible == 0
		|| map->numcollectible > 1)
		return (ft_putendl(INV_PLAYEREXITCOLL), false);
	return (true);
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

void	free_parser_map(t_map *map)
{
	if (map->map)
		free_file(map->map);
	if (map->visited)
		free_file((char **)map->visited);
}
