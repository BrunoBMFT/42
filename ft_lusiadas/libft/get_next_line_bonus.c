/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:35:20 by brfernan          #+#    #+#             */
/*   Updated: 2024/01/22 21:41:21 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			trig;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1 || FOPEN_MAX <= fd)
	{
		if (fd > 0 && FOPEN_MAX > fd)
			clearbuf(buf[fd]);
		return (NULL);
	}
	line = NULL;
	trig = 0;
	while (trig == 0 && (buf[fd][0] || read(fd, buf[fd], BUFFER_SIZE)))
	{
		line = ft_strjoin_gnl(line, buf[fd]);
		if (!line)
			return (NULL);
		trig = buffer(buf[fd]);
	}
	return (line);
}
/*int	main(void)
{
	int	fd;
	char *ret;

	fd = open("/nfs/homes/brfernan/Documents/example.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error in opening file");
		return (1);
	}
	ret = get_next_line(fd);
	while (ret)
	{
		printf("%s", ret);
		free(ret);
		ret = get_next_line(fd);
	}
	close(fd);
	return (0);
}*/