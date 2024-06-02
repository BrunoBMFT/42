/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:35:20 by brfernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:59:01 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*get_next_line(char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	int			trig;

	if (BUFFER_SIZE <= 0 || read(0, 0, 0) == -1)
		return (clearbuf(buf));
	trig = 0;
	while (trig == 0 && (buf[0] || read(0, buf, BUFFER_SIZE)))
	{
		*line = gnl_ft_strjoin(*line, buf);
		if (!*line)
			return (NULL);
		trig = buffer(buf);
	}
	return (*line);
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
		ft_printf("%s", ret);
		free(ret);
		ret = get_next_line(fd);
	}
	close(fd);
	return (0);
}*/