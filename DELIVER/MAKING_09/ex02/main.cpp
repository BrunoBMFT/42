#include "PmergeMe.hpp"

bool	validArgs(int ac, char **av) {
	if (ac < 2)
		return (false);
	for (size_t i = 1; av[i]; i++) {
		std::string temp = av[i];
		if (temp.size() > 10 || std::atol(temp.c_str()) > INT_MAX || std::atol(temp.c_str()) < 0)
			return (false);
		for (size_t j = 0; j < temp.size(); j++)
			if (!isdigit(temp[j]))
				return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	if (!validArgs(ac, av))
		return (std::cerr << "Usage: ./PmergeMe <digits-only>\n", 1);
	//parse
	
	int size = printBefore(av);
	double listTime, dequeTime;

	clock_t startList = clock();
	PmergeMeList(av);
	listTime = static_cast<double>(clock() - startList) / 1000;
	
	clock_t startDeque = clock();
	PmergeMeDeque(av);
	dequeTime = static_cast<double>(clock() - startDeque) / 1000;

	std::cout << "Time to process a range of " << size
		<< " elements with std::list : " << listTime / 1000
		<< " us" << std::endl;
	std::cout << "Time to process a range of " << size
		<< " elements with std::deque : " << dequeTime / 1000
		<< " us" << std::endl;

	return (0);
}