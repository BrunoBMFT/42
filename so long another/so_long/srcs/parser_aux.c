/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:24:20 by bruno             #+#    #+#             */
/*   Updated: 2024/04/25 19:37:02 by brfernan         ###   ########.fr       */
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
