#include "get_next_line_bonus.h"

int	buffer(char	*buf)
{
	int	trig = 0, i = 0, j = 0;
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
	int	i = 0;
	while (buf[i])
		buf[i++] = 0;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line = NULL;
	int			trig = 0;
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1 || FOPEN_MAX <= fd)
	{
		if (fd > 0 && FOPEN_MAX > fd)
			clearbuf(buf[fd]);
		return (NULL);
	}
	while (trig == 0 && (buf[fd][0] || read(fd, buf[fd], BUFFER_SIZE)))
	{
		line = ft_strjoin_gnl(line, buf[fd]);
		if (!line)
			return (NULL);
		trig = buffer(buf[fd]);
	}
	return (line);
}