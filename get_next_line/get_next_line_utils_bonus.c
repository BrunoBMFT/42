/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:35:23 by brfernan          #+#    #+#             */
/*   Updated: 2023/11/17 18:55:35 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
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

char	*ft_strjoin(char *line, char *buf)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(line) + ft_strlen(buf) + 1);
	if (!str)
		return (0);
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
