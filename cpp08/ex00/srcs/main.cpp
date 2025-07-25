#include "../includes/easyfind.hpp"
// ANOTHER ERROR VALUE
int	main(void){
	std::vector<int> container;

	for (int i = 0; i < 5; i++)
		container.push_back(i * 3);

	std::cout << "list: ";
	for (int i = 0; i < 5; i++)
		std::cout << container[i] << " ";
	std::cout << std::endl;
	
	{
		std::cout << "first test:" << std::endl;
		int tofind = 6;
		std::cout << "find: " << tofind << " inside the list" << std::endl;
		int n = ::easyfind(container, tofind);
		std::cout << "found " << tofind << " at pos: " << n << std::endl;
		std::cout << std::endl;
	}


	{
		std::cout << "second test:" << std::endl;
		int tofind = 5;
		std::cout << "find: " << tofind << " inside the list" << std::endl;
		int n = ::easyfind(container, tofind);
		std::cout << "found " << tofind << " at pos: " << n << std::endl;
	}

}