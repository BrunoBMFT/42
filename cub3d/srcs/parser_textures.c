/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:41:37 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/07 19:38:10 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	path_already_saved(t_data *data, char *temp)
{
	if ((!ft_strncmp("NO", temp, 2) && data->path_north)
		|| (!ft_strncmp("EA", temp, 2) && data->path_east)
		|| (!ft_strncmp("SO", temp, 2) && data->path_south)
		|| (!ft_strncmp("WE", temp, 2) && data->path_west)
		|| (!ft_strncmp("F", temp, 1) && data->path_floor)
		|| (!ft_strncmp("C", temp, 1) && data->path_ceiling))
		return (true);
	return (false);
}

bool	save_texture_path(t_data *data)
{
	int		i;

	i = 0;
	while (data->file[i])
	{
		if (path_already_saved(data, data->file[i]))
			return (error("Duplicate paths"));
		if (!ft_strncmp("NO", data->file[i], 2))
			data->path_north = ft_strtrim(data->file[i] + 2, " \t");
		else if (!ft_strncmp("EA", data->file[i], 2))
			data->path_east = ft_strtrim(data->file[i] + 2, " \t");
		else if (!ft_strncmp("SO", data->file[i], 2))
			data->path_south = ft_strtrim(data->file[i] + 2, " \t");
		else if (!ft_strncmp("WE", data->file[i], 2))
			data->path_west = ft_strtrim(data->file[i] + 2, " \t");
		else if (!ft_strncmp("F", data->file[i], 1))
			data->path_floor = ft_strtrim(data->file[i] + 1, " \t");
		else if (!ft_strncmp("C", data->file[i], 1))
			data->path_ceiling = ft_strtrim(data->file[i] + 1, " \t");
		i++;
	}
	return (true);
}

//verify if working
bool	check_paths(t_data *data)
{
	if (access(data->path_north, R_OK) || access(data->path_east, R_OK)
		|| access(data->path_south, R_OK) || access(data->path_west, R_OK))
		return (error("missing texture"));
	return (true);
}

// TODO check limits and commas
bool	color_char_check(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_strchr("0123456789,", color[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	texture_check(t_data *data)
{
	if (!data->path_north || !data->path_east || !data->path_south
		|| !data->path_west || !data->path_floor || !data->path_ceiling)
		return (error("Missing info"));
	if (!*data->path_ceiling || !*data->path_floor)
		return (error("Missing info"));
	if (!color_char_check(data->path_ceiling)
		|| !color_char_check(data->path_floor))
		return (error("Invalid colors"));
	return (true);
}
