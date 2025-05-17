#include <iostream>
#include <string>

int main() {
	std::string str = "HI THIS IS BRAIN";
	std::string *stringPTR = &str;
	std::string stringREF = str;

	std::cout << "address of string:\t" << &str << std::endl;
	std::cout << "address of stringPTR:\t" << stringPTR << std::endl;
	std::cout << "address of stringREF:\t" << &stringREF << std::endl;
	std::cout << std::endl;
	std::cout << "value of string:\t" << str << std::endl;
	std::cout << "value of stringPTR:\t" << *stringPTR << std::endl;
	std::cout << "value of stringREF:\t" << stringREF << std::endl;

	return 0;
}
