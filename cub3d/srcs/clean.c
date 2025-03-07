/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:36:01 by bruno             #+#    #+#             */
/*   Updated: 2025/03/07 18:12:31 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clean_texture_path(t_data *data)//have this run after img is saved
{
	if (data->p_north)
		free(data->p_north);
	if (data->p_east)
		free(data->p_east);
	if (data->p_south)
		free(data->p_south);
	if (data->p_west)
		free(data->p_west);
	if (data->c_floor)
		free(data->c_floor);
	if (data->c_ceiling)
		free(data->c_ceiling);
}

//mlx, window
int	clean_everything(t_data *data)
{
	if (!data)
		return (0);
	if (data->file)
		free_array(data->file);
	if (data->map)
		free_array(data->map);
	clean_texture_path(data);
	return (0);
}
