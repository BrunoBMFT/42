#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	if (ac < 2)
		return (std::cerr << "Not enough\n", 1);
	//parse
	std::cout << "List: \n";
	PmergeMeList(av);


	return (0);
}