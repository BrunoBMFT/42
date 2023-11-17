/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:35:20 by brfernan          #+#    #+#             */
/*   Updated: 2023/11/17 18:55:13 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			trig;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (clearbuf(buf));
	line = NULL;
	trig = 0;
	while (trig == 0 && (buf[0] || read(fd, buf, BUFFER_SIZE)))
	{
		line = ft_strjoin(line, buf);
		trig = buffer(buf);
	}
	return (line);
}
