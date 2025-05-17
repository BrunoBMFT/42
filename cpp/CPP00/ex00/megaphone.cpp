#include <iostream>

void	print_args(char *str)
{
	for (int i = 0; str[i]; i++){
		char c = toupper(str[i]);
		std::cout << c;
	}
}

int main(int ac, char **av) 
{
	if (ac == 1){
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return 0;
	}
	for (int i = 1; av[i]; i++){
		print_args(av[i]);
	}
	std::cout << std::endl;


	return 0;
}
