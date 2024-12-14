/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:48 by bruno             #+#    #+#             */
/*   Updated: 2024/12/14 02:24:41 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	char_allowed(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (!ft_strchr(POSSIBLE, str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_map_exists(t_data *data)//use the function above?
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (!ft_strchr("01NESW", data->map[y][x]))
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}

void	save_map(t_data *data)
{
	int	i;
	int	count;
	int	start;
	int	j;

	i = 0;
	count = 0;
	start = 0;
	while (data->parser->file[i])
	{
		if (char_allowed(data->parser->file[i]))
			count++;
		if (count == 1)
			start = i;
		i++;
	}
	data->map = ft_calloc(sizeof(char *), count + 2);
	if (!data->map)
		error(data, "Map allocation failed");
	i = start;
	j = 0;
	while (data->parser->file[i])
	{
		if (char_allowed(data->parser->file[i]))
		{
			data->map[j] = ft_strdup(data->parser->file[i]);
			if (!data->map[j])
				error(data, "Map strdup failed");
			j++;
		}
		i++;
	}
	data->map[j] = NULL;
	if (!check_map_exists(data))
		error(data, "No map");
}
