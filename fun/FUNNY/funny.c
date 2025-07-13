#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"

void	new_condition(int fd, int i)
{
	write(fd, "\tif (number == ", 15);
	ft_putnbr_fd(i, fd);
	write(fd, ")\n\t\treturn (\"", 13);
	if (ft_is_even(i))
		write(fd, "even", 4);
	else
		write(fd, "odd", 3);
	write(fd, "\");\n", 4);
}

int	main(void)
{
	int fd = open("lol.c",  O_CREAT | O_RDWR, 0777);
	write(fd, "char *even_or_odd(int number)\n{\n", 32);
	for (int i = 0; i < 1000; i++)
		new_condition(fd, i);
	write(fd, "}\n", 2);
	//write a main for this?
}