#include <unistd.h>

int	iter(char *str, char c, int len)// checks if c is in str, and returns 1 if it is
{
	int	i = 0;

	while (str[i] && (i < len || len == -1))
		if (str[i++] == c)
			return (1);
	return (0);
}

int	main(int ac, char **av)
{
	int	i;

	if (ac == 3)
	{
		i = 0;
		while (av[1][i])
		{
			if (!iter(av[1], av[1][i], i) && iter(av[2], av[1][i], -1))
				write(1, &av[1][i], 1);
			i += 1;
		}
	}
	write(1, "\n", 1);
	return (0);
}