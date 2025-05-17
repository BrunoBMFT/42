/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:35:23 by brfernan          #+#    #+#             */
/*   Updated: 2024/12/16 04:08:46 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*gnl_ft_strjoin(char *line, char *buf)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = malloc(gnl_ft_strlen(line) + gnl_ft_strlen(buf) + 1);
	if (!str)
		return (free (line), NULL);
	while (line && line[i])
	{
		str[i] = line[i];
		i++;
	}
	while (buf && buf[j])
	{
		str[i++] = buf[j];
		if (buf[j] == '\n')
			break ;
		j++;
	}
	str[i] = 0;
	free (line);
	return (str);
}

int	buffer(char	*buf)
{
	int	trig;
	int	i;
	int	j;

	trig = 0;
	i = 0;
	j = 0;
	while (buf[i])
	{
		if (trig == 1)
		{
			buf[j] = buf[i];
			j++;
		}
		if (buf[i] == '\n')
			trig = 1;
		buf[i++] = 0;
	}
	return (trig);
}

char	*clearbuf(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
		buf[i++] = 0;
	return (NULL);
}
