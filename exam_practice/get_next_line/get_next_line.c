# include <unistd.h>
# include <stdlib.h>	
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (src[i])
	{
	   dest[i] = src[i];
	   i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		line[70000];
	static int	bytes_read;
	static int 	pos;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (pos >= bytes_read)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			pos = 0;
			if (bytes_read <= 0)
				break ;
		}
		// line[i] = buffer[pos];//fix?
		// if (buffer[pos++] == '\n')//fix?
		// 	break ;//fix?
		if (line[i] == '\n')//git version
			break ;//git version
		line[i] = buffer[pos++];//git version
		i++;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}
/* 
int main()
{
    int fd = open("./txt.txt", O_RDONLY);
    printf("%s", get_next_line(fd));
    return (0);
} */
