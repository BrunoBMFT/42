/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:02:47 by brfernan          #+#    #+#             */
/*   Updated: 2025/05/12 15:01:57 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

bool	is_path(char *str)
{
	char	*temp;

	temp = skip_spaces(str);
	if (!ft_strncmp("NO", temp, 2) || !ft_strncmp("SO", temp, 2)
		|| !ft_strncmp("WE", temp, 2) || !ft_strncmp("EA", temp, 2)
		|| !ft_strncmp("F", temp, 1) || !ft_strncmp("C", temp, 1))
		return (true);
	return (false);
}

bool	is_empty(const char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (!(*str == ' ' || *str == '\t' || *str == '\n'
				|| *str == '\r' || *str == '\v' || *str == '\f'))
			return (false);
		str++;
	}
	return (true);
}

int	line_count(t_data *data, int *i)
{
	int	count;
	int	start;

	*i = 0;
	count = 0;
	start = 0;
	while (data->file[*i])
	{
		if (!is_path(data->file[*i]))
			count++;
		if (count == 1)
			start = *i;
		(*i)++;
	}
	*i = start - 1;
	return (count);
}

bool	check_islands(t_data *data)
{
	int		i;
	bool	map_started;
	bool	map_ended;

	i = 0;
	map_started = false;
	map_ended = false;
	while (data->file[i])
	{
		if (!is_path(data->file[i]) && is_empty(data->file[i]) && map_started)
			map_ended = true;
		if (!is_path(data->file[i]) && !is_empty(data->file[i]))
		{
			if (map_ended)
				return (false);
			map_started = true;
		}
		i++;
	}
	return (true);
}

bool	save_map(t_data *data)
{
	int		i;
	int		j;

	if (!check_islands(data))
		return (error("Map has islands"));
	data->map = ft_calloc(sizeof(char *), line_count(data, &i) + 1);
	if (!data->map)
		return (error("Map allocation failed"));
	j = 0;
	while (data->file[++i])
	{
		if (data->is_map && !is_empty(data->file[i]) && is_path(data->file[i]))
			return (error("Map is invalid"));
		if ((!is_empty(data->file[i]) || data->is_map)
			&& !is_path(data->file[i]))
		{
			data->is_map = true;
			data->map[j] = ft_strdup(data->file[i]);
			if (!data->map[j++])
				return (error("Map strdup failed"));
		}
	}
	return (true);
}
