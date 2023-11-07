/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:35:20 by brfernan          #+#    #+#             */
/*   Updated: 2023/11/06 21:03:31 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	buffer(char	*buf) //???
{
	int	trig; //trigger for newline
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
		if (buf[i] == '\n') //trigger for newline
			trig = 1;
		buf[i] = 0;
		i++;
	}
	return (trig);
}

void	clearbuf(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		buf[i] = 0; // every index of buffer is 0
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];	//buf is the size defined in .h + 1 because char
	char		*line;
	int			trig;
	
	//buf neg wouldnt read anything.
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1) 
	{
		clearbuf(buf);
		return (NULL);
	}
	line = NULL;
	trig = 0;
	//
	//
	//if read is 0, means file is over
	while (trig == 0 && (buf[0] || read(fd, buf, BUFFER_SIZE)))
	{
		line = ft_strjoin(line, buf);
		trig = buffer(buf); // to know if there's a \n
		//if there is a \n, it returns line when it checks loop condition
	}
	return (line);
}

/*int	main(void)
{
	int	fd;
	char *ret;

	fd = open("/nfs/homes/brfernan/Documents/example.txt", O_RDONLY);  //fd is defined in main
	if (fd == -1) // -1 is always error
	{
		perror("Error in opening file");
		return (1);
	}
	ret = get_next_line(fd);
	while (ret) //runs while ret != \0 aka end of file
	{
		printf("%s", ret);
		free(ret); // free so no mem leaks
		ret = get_next_line(fd); //needs loop because it gets one line at a time
	}
	close(fd); //similar to free?
	return (0);
}*/