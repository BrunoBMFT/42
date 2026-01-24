#include "../includes/PmergeMe.hpp"

void	parseData(int ac, char **args)
{
	if (ac < 2)
		throw std::runtime_error("Invalid arguments: not enough");
	for (int i = 1; args[i]; i++) {
		for (int j = 0; args[i][j]; j++) {
			if (!isdigit(args[i][j])) //typecast?
				throw std::runtime_error("Invalid arguments: not digits");
		}
		for (int j = 1; args[j]; j++) {
			if ((std::string(args[i]) == std::string(args[j])) && i != j)//why only works with string
				throw std::runtime_error("Invalid arguments: duplicates");
		}
	}
}

int main(int ac, char **av)
{
	try {
		parseData(ac, av);//put in class
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	PmergeMe shit(av);



	shit.execute();//execute command


	return (0);
}
