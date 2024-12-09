/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:48 by bruno             #+#    #+#             */
/*   Updated: 2024/12/09 12:29:58 by bruno            ###   ########.fr       */
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
	if (count == 0)
		error(data, "No map");
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
