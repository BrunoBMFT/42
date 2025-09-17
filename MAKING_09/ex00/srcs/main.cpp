#include "../includes/BitcoinExchange.hpp"
#include <fstream>


int main()
{
	std::ifstream file("../data.csv");//in relation to compilation
	if (!file) {
		std::cout << "file not opened\n";
		return 1;
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::cout << line << std::endl;
	}
	return 0;
}
