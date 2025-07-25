#include "../includes/Iter.hpp"

void	my_putc(char const &c){
	std::cout << c;
}

int	main(void){
	std::string str = "hello";
	size_t len = 3;
	::iter(str.c_str(), len, my_putc);
	std::cout << std::endl;
	return 0;
}

