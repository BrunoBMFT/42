#include "../includes/Span.hpp"

int	main(void){
	std::srand(time(NULL));
	{
		std::cout << "TEST 1:" << std::endl;
		Span sp = Span(5);
		sp.addNumber(1);
		sp.addNumber(2);
		sp.addNumber(15);
		sp.addNumber(9);
		sp.addNumber(12);
		try {
			sp.addNumber(9);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	
		try {
			std::cout << "shortest: " << sp.shortestSpan() << std::endl;
			std::cout << "longest: " << sp.longestSpan() << std::endl;
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	{
		std::cout << "\nTEST 2:" << std::endl;
		Span sp = Span(100);
		std::vector<int> temp;
		for (int i = 0; i < 100; i++)
			temp.push_back(rand() % 1000000);
		try {
			sp.addNumber(temp.begin(), temp.end());
			std::cout << "shortest: " << sp.shortestSpan() << std::endl;
			std::cout << "longest: " << sp.longestSpan() << std::endl;
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
}