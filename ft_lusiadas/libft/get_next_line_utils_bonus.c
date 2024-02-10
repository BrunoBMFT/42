#include "get_next_line_bonus.h"

int	ft_strlen_gnl(char *str)
{
	int	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *line, char *buf)
{
	char	*str = malloc(ft_strlen_gnl(line) + ft_strlen_gnl(buf) + 1);
	size_t	i = 0, j = 0;
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
