#include "../includes/iter.hpp"

void my_toupper(char &c){
	c = std::toupper(c);
}

void my_tolower(char &c){
	c = std::tolower(c);
}

void	my_putc(char const &c) {
	std::cout << c;
}

int	main(void){
	char a[] = {'a', 'b', 'c'};
	::iter(a, 3, my_toupper);
	std::cout << a[0] << " " << a[1] << " " << a[2] << std::endl;
	::iter(a, 3, my_tolower);
	std::cout << a[0] << " " << a[1] << " " << a[2] << std::endl;


	std::string str = "hello";
	::iter(str.c_str(), str.length(), my_putc);
	std::cout << std::endl;
	::iter(str.c_str(), str.length(), my_putc);
	return 0;
}

