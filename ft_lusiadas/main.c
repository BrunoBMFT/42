
#include "libft/libft.h"
#include <fcntl.h>

int	main(void)
{
	int	fd = open("/home/bruno/42/ft_lusiadas/lusiadas.txt", O_RDONLY), count = -2;
	char *ret = get_next_line(fd);
	while (ret)
	{
		ft_printf("%s", ret);
		free(ret);
		if (count % 8 == 0)
			ft_printf("\n");
		ret = get_next_line(fd);
		count++;
	}
	close(fd);
	return (0);
}