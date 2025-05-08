/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:41:37 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/14 17:23:29 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	path_already_saved(t_data *data, char *temp)
{
	if ((!ft_strncmp("NO", temp, 2) && data->path_north)
		|| (!ft_strncmp("EA", temp, 2)
			&& data->path_east)
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

int	parse_rgb(const char *str)
{
	int	i;
	int	start;
	int	red;
	int	green;
	int	blue;

	i = 0;
	start = 0;
	while (str[i] && str[i] != ',')
		i++;
	red = ft_atoi(&str[start]);
	start = ++i;
	while (str[i] && str[i] != ',')
		i++;
	green = ft_atoi(&str[start]);
	start = ++i;
	blue = ft_atoi(&str[start]);
	return ((red << 16) | (green << 8) | blue);
}

bool	color_char_check(char *color)
{
	int	i;
	int	value;
	int	count;

	i = 0;
	count = 0;
	while (count < 3)
	{
		if (color[i] < '0' || color[i] > '9')
			return (false);
		value = 0;
		while (color[i] >= '0' && color[i] <= '9')
			value = value * 10 + (color[i++] - '0');
		if (value < 0 || value > 255)
			return (false);
		count++;
		if (count < 3)
		{
			if (color[i++] != ',')
				return (false);
		}
	}
	if (color[i] != '\0')
		return (false);
	return (true);
}

bool	texture_check(t_data *data)
{
	if (!data->path_north || !data->path_east || !data->path_south
		|| !data->path_west || !data->path_floor || !data->path_ceiling)
		return (error("Missing info"));
	if (!*data->path_ceiling || !*data->path_floor)
		return (error("Missing info"));
	if (!color_char_check(data->path_floor)
		|| !color_char_check(data->path_ceiling))
		return (error("Invalid colors"));
	data->color_floor = parse_rgb(data->path_floor);
	data->color_ceiling = parse_rgb(data->path_ceiling);
	if (access(data->path_north, R_OK) || access(data->path_east, R_OK)
		|| access(data->path_south, R_OK) || access(data->path_west, R_OK))
		return (error("missing texture"));
	return (true);
}
