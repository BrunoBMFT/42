/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:36:01 by bruno             #+#    #+#             */
/*   Updated: 2024/12/14 14:25:03 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clean_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free (arr[i]);
		i++;
	}
	free (arr);
}

void	clean_bool(bool **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free (arr[i]);
		i++;
	}
	free (arr);
}

void	clean_textures(t_data *data)
{
	if (data->p_north)
		free(data->p_north);
	if (data->p_east)
		free(data->p_east);
	if (data->p_south)
		free(data->p_south);
	if (data->p_west)
		free(data->p_west);
	// if (data->c_floor)
	// 	free(data->c_floor);
	// if (data->c_ceiling)
	// 	free(data->c_ceiling);
}
//mlx, window
int	clean_everything(t_data *data)
{
	if (!data)
		return (0);
	if (data->file)
		clean_array(data->file);
	if (data->visited)
		clean_bool(data->visited);
	if (data->map)
		clean_array(data->map);
	if (data->mlx)
		free (data->mlx);
	clean_textures(data);
	return (0);
}
