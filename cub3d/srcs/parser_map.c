/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:48 by bruno             #+#    #+#             */
/*   Updated: 2024/12/10 16:11:13 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	char_allowed(char *str)
{
	int i = 0;
	
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

void	save_map(t_data *data)
{
	int i = 0;
	int count = 0;
	int start = 0;
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
	int j = 0;
	while (data->file[i])
	{
		if (char_allowed(data->file[i]))
		{
			data->map[j] = ft_strdup(data->file[i]);
			if (!data->map[j])
				error(data, "Map strdupo failed");
			j++;
		}
		i++;
	}
	data->map[j] = NULL;
}

void	save_texture_path(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->file[i])
	{
		temp = data->file[i];
		if (ft_strncmp("NO", temp, 2) == 0)
			data->p_north = ft_strdup(temp + 3);
		if (ft_strncmp("EA", temp, 2) == 0)
			data->p_east = ft_strdup(temp + 3);
		if (ft_strncmp("SO", temp, 2) == 0)
			data->p_south = ft_strdup(temp + 3);
		if (ft_strncmp("WE", temp, 2) == 0)
			data->p_west = ft_strdup(temp + 3);
		if (ft_strncmp("F", temp, 1) == 0)
			data->c_floor = ft_strdup(temp + 2);
		if (ft_strncmp("C", temp, 1) == 0)
			data->c_ceiling = ft_strdup(temp + 2);
		i++;
	}
}
