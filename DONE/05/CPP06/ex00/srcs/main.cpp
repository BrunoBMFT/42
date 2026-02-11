#include "../includes/ScalarConverter.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cout << "Wrong number of arguments\n";
		return 0;
	}
	ScalarConverter::convert(av[1]);
	return 0;
}