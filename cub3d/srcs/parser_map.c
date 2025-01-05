/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:48 by bruno             #+#    #+#             */
/*   Updated: 2025/01/05 04:18:05 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	char_allowed(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(POSSIBLE, str[i]))
			return (false);
		i++;
	}
	return (true);
}
//broken

// 1111111111111111111111111
// 1000000000110000000000001
// 1011000001110000000000001
// 10010000000000000N0000001
// 1111111111111111111111111
bool	check_map_exists(t_data *data)//use the function above?
{
	int	y;
	int	x;


	//this skips empty lines, make it skip just tabs or spaces?
	int i = 0;
	int j = 0;
	while (data->map[i])
	{
		if (!*data->map[i])
		{
			i++;
			continue ;
		}
		data->map[j] = data->map[i];
		i++;
		j++;
	}
	data->map[j] = 0;
	//this skips empty lines, make it skip just tabs or spaces?


	
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (!ft_strchr("01NESW ", data->map[y][x]))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
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
	data->max_len = 0;
	int	temp;
	while (data->file[i])
	{
		if (char_allowed(data->file[i]))
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
	while (data->file[i])
	{
		if (char_allowed(data->file[i]))
		{
			data->map[j] = ft_strdup(data->file[i]);
			if (!data->map[j])
				error(data, "Map strdup failed");
			temp = ft_strlen(data->file[i]);
			if (data->max_len < temp)
				data->max_len = temp;
			j++;
		}
		i++;
	}
	data->map[j] = NULL;
	if (!check_map_exists(data))
		error(data, "No map");
}
