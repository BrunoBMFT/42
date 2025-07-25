/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:35:20 by brfernan          #+#    #+#             */
/*   Updated: 2025/07/16 18:01:34 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

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
		line = gnl_ft_strjoin(line, buf);
		if (!line)
			return (NULL);
		trig = buffer(buf);
	}
	return (line);
}

char	*get_next_line_bonus(int fd)
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
		line = gnl_ft_strjoin(line, buf[fd]);
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