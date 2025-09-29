#include "../includes/RPN.hpp"

int main(int ac, char **av)
{
	RPN rpn;
	if (ac != 2)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
	if (!rpn.validString(av[1]))
		return 1;

	rpn.execute(av[1]);
	
	return (0);
}
