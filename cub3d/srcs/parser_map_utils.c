/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:02:47 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/07 20:03:21 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_allowed(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr("01NESWD ", str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_path(char *str)
{
	if (!ft_strncmp("NO", str, 2) || !ft_strncmp("SO", str, 2)
		|| !ft_strncmp("WE", str, 2) || !ft_strncmp("EA", str, 2)
		|| !ft_strncmp("F", str, 1) || !ft_strncmp("C", str, 1))
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
	*i = start;
	return (count);
}

bool	save_map(t_data *data)
{
	int		i;
	int		j;
	bool	is_map;

	data->map = ft_calloc(sizeof(char *), line_count(data, &i) + 2);
	if (!data->map)
		return (error("Map allocation failed"));
	j = 0;
	is_map = false;
	while (data->file[i])
	{
		if ((!is_empty(data->file[i]) || is_map)
			&& !is_path(data->file[i]))
		{
			is_map = true;
			data->map[j] = ft_strdup(data->file[i]);
			if (!data->map[j])
				return (error("Map strdup failed"));
			j++;
		}
		i++;
	}
	data->map[j] = NULL;
	return (true);
}
