#include "./philosophers.h"

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse(char **av)
{
	int		i;
	size_t	num;

	i = 1;
	while (av[i])
	{
		if (!ft_is_number(av[i]))
		{
			printf("Error!\nNot a number\n");
			return (0);
		}
		num = ft_atol(av[i]);
		if (num <= 0 || num > INT_MAX)
		{
			printf("Error!\nWrong size\n");
			return (0);
		}
		i++;
	}
	return (1);
}
