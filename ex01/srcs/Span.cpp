#include "../includes/Span.hpp"

Span::Span() : max(0) {}
Span::Span(unsigned int n) : max(n) {}

//COPIES
Span::~Span() {}


void Span::addNumber(int num) {
	//check if its overfilling
	// if (vect.size() >= max)
	// 	throw FullContainerException();
	vect.push_back(num);
}

int Span::biggestSpan() {
	// if (vect.size() <= 2)
	// 	throw NotEnoughNumbersException();
	int smallest = 2147483647;//use macro
	int biggest = 0;
	//USE SORT
	for (size_t i = 0; i < vect.size(); i++) {
		if (vect[i] < smallest)
			smallest = vect[i];
		if (vect[i] > biggest)
			biggest = vect[i];
		std::cout << smallest << " " << biggest << std::endl;
	}
	return (biggest - smallest);//seems like i built the biggest span
}


int Span::shortestSpan() {
	// if (vect.size() <= 2)
	// 	throw NotEnoughNumbersException();


	return (0);//seems like i built the biggest span
}








// // Exceptions 
// // !RENAME
// class FullContainerException : public std::exception
// {
// 	public:
// 		virtual const char *what() const throw();
// };

// class NotEnoughNumbersException : public std::exception
// {
// 	public:
// 		virtual const char *what() const throw() {}
// };