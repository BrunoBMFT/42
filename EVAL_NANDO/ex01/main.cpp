#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
		return 1;
	RPN a(av[1]);
	return 0;
}
