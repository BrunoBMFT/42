
#include "libft/libft.h"
#include <fcntl.h>

int	main(void)
{
	int	fd;
	char *ret;

	fd = open("/home/brfernan/42/ft_lusiadas/lusiadas.txt", O_RDONLY);
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
}