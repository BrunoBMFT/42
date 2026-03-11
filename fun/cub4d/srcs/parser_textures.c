#include "../includes/cub3d.h"

bool	path_already_saved(t_data *data, char *temp)
{
	if ((!ft_strncmp("NO", temp, 2) && data->paths[NORTH])
		|| (!ft_strncmp("EA", temp, 2) && data->paths[EAST])
		|| (!ft_strncmp("SO", temp, 2) && data->paths[SOUTH])
		|| (!ft_strncmp("WE", temp, 2) && data->paths[WEST])
		|| (!ft_strncmp("F", temp, 1) && data->paths[FLOOR])
		|| (!ft_strncmp("C", temp, 1) && data->paths[CEILING]))
		return (true);
	return (false);
}

bool	save_texture_path(t_data *data)
{
	int		i;
	char	*line;

	i = 0;
	while (data->file[i])
	{
		line = skip_spaces(data->file[i]);
		if (path_already_saved(data, line))
			return (error("Duplicate paths"));
		if (!ft_strncmp("NO", line, 2))
			data->paths[NORTH] = ft_strtrim(line + 2, WHITESPACE);
		else if (!ft_strncmp("EA", line, 2))
			data->paths[EAST] = ft_strtrim(line + 2, WHITESPACE);
		else if (!ft_strncmp("SO", line, 2))
			data->paths[SOUTH] = ft_strtrim(line + 2, WHITESPACE);
		else if (!ft_strncmp("WE", line, 2))
			data->paths[WEST] = ft_strtrim(line + 2, WHITESPACE);
		else if (!ft_strncmp("F", line, 1))
			data->paths[FLOOR] = remove_spaces(ft_strtrim(line + 1, WHITESPACE));
		else if (!ft_strncmp("C", line, 1))
			data->paths[CEILING] = remove_spaces(ft_strtrim(line + 1, WHITESPACE));
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
	if (!data->paths[NORTH] || !data->paths[EAST] || !data->paths[SOUTH]
		|| !data->paths[WEST] || !data->paths[FLOOR] || !data->paths[CEILING])
		return (error("Missing info"));
	if (!color_char_check(data->paths[FLOOR]) || !color_char_check(data->paths[CEILING]))
		return (error("Invalid colors"));
	data->color_floor = parse_rgb(data->paths[FLOOR]);
	data->color_ceiling = parse_rgb(data->paths[CEILING]);
	if (access(data->paths[NORTH], R_OK) || access(data->paths[EAST], R_OK)
		|| access(data->paths[SOUTH], R_OK) || access(data->paths[WEST], R_OK))
		return (error("Missing texture"));
	return (true);
}
