//#include <stdio.h>

int	max(int* tab, unsigned int len)
{
	if (len == 0)
		return (0);
	unsigned int	i = 0;
	int	biggest = 0;

	while (i < len)
	{
		if (biggest < tab[i])
			biggest = tab[i];
		i++;
	}

	return (biggest);
}

/*int	main(void)
{
	int tab[7] = {1, 3, 4, 5, 6, 0, 2};


	printf("%d", max(tab, 9));
}*/