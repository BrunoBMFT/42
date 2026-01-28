#include <iostream>
#include <vector>
#include <sstream>

int	main(void)
{
	std::string line = "Hi\t i am\n world                  whatup";
	std::istringstream iss(line);
	std::vector<std::string> arguments;
	std::string temp;
	while(iss >> temp) // <chName> ol Miguel 100?
		arguments.push_back(temp);
	for (int i = 0; i < arguments.size(); i++) {
		std::cout << i << ": [" << arguments[i] << "]\n";
	}
}