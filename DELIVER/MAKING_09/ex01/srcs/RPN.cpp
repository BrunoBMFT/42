#include "../includes/RPN.hpp"

//*CONSTRUCTORS
RPN::RPN()
{

}

RPN::RPN(const RPN& oth) {
	*this = oth;
}

RPN RPN::operator=(const RPN& oth)
{
	return (*this);
}

RPN::~RPN() {}



//*FUNCTIONS

//*EXCEPTIONS
const char *RPN::Exception::what() const throw() {
	return ("ANY EXCEPTION LOL.");
}

