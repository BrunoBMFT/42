#include <unistd.h>

int	main(int ac, char **av)
{
	int	i = 0;
	int c;
	if (ac == 2)
	{
		while (av[1][i])
		{
			c = av[1][i];
			if ((av[1][i] >= 'a' && av[1][i] <= 'm') || (av[1][i] >= 'A' && av[1][i] <= 'M'))
				c += 13;
			else if ((av[1][i] >= 'n' && av[1][i] <= 'z') || (av[1][i] >= 'N' && av[1][i] <= 'Z'))
				c -= 13;
			write(1, &c, 1);
			i++;
		}
	}
	write(1, "\n", 1);
}