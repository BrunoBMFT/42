#include "../includes/Span.hpp"

//*CONSTRUCTORS
Span::Span() : maxSize(0) {}
Span::Span(unsigned int n) : maxSize(n) {}

Span::Span(const Span &oth) {
	*this = oth;
}

Span &Span::operator=(const Span &oth) {
	if (this != &oth) {
		maxSize = oth.maxSize;
		vect = oth.vect;
	}
	return (*this);
}

Span::~Span() {}

//*FUNCTIONS
void Span::addNumber(int num) {
	if (vect.size() >= maxSize)
		throw FullContainer();
	vect.push_back(num);
}

void	Span::addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
	if (vect.size() + std::distance(begin, end) > maxSize)
		throw FullContainer();
	vect.insert(vect.end(), begin, end);
}

int Span::shortestSpan() {
	if (vect.size() <= 1)
		throw NotEnoughNumbers();
	std::vector<int> temp = vect;
	std::sort(temp.begin(), temp.end());
	int min = temp[1] - temp[0];
	for (unsigned int i = 1; i < temp.size(); i++) {
		if (temp[i] - temp[i - 1] < min)
			min = temp[i] - temp[i - 1];
	}
	return (min);
}

int Span::longestSpan() {
	if (vect.size() <= 1)
		throw NotEnoughNumbers();
	int biggest = vect[0], smallest = vect[0];
	for (unsigned int i = 0; i < vect.size(); i++) {
		if (vect[i] < smallest)
			smallest = vect[i];
		else if (vect[i] > biggest)
			biggest = vect[i];
	}
	return (biggest - smallest);
}

//*EXCEPTIONS
const char *Span::FullContainer::what() const throw()
{ return ("Container is full"); }

const char *Span::NotEnoughNumbers::what() const throw()
{ return ("Not enough numbers in container"); }