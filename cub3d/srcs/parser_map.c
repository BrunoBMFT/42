/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:48 by bruno             #+#    #+#             */
/*   Updated: 2024/12/06 15:25:37 by bruno            ###   ########.fr       */
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

bool	is_separator(char *str)
{
	if (!str || !*str)
		return (false);
}
//instead of saving only what is map, save everything but paths and colors by skipping them 
//  while saving the map.
//let flood fill resolve if there are \n or incorrect borders, it will find them either way
//just give start pos to floodfill and let it find everything needed
void	save_map(t_data *data)
{
	int i = 0;
	int count = 0;
	while (data->file[i])
	{
		if (*data->file[i] && char_allowed(data->file[i]))
			count++;
		if (count != 0 && (!data->file[i] || !*data->file[i]))
			error(data, "wtf");
		i++;
	}
	
	data->map = ft_calloc(sizeof(char *), count + 1);
	if (!data->map)
		error(data, "Map allocation failed");

	i = 0;
	int j = 0;
	//take care of borders (surrounded by 1) in flood
	while (data->file[i])
	{
		if (*data->file[i] && char_allowed(data->file[i]))
		{
			data->map[j] = ft_strdup(data->file[i]);
			j++;
		}
		i++;
	}
	data->map[j] = NULL;
}
