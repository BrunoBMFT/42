#include "Fixed.h"

void	Fixed::setRawBits(int const raw){
	this->_raw = raw;
}

int		Fixed::getRawBits(void) const{
	std::cout << "getRawBits member function called\n";
	return this->_raw;
}

Fixed::Fixed(){
	setRawBits(0);
	std::cout << "Default constructor called\n";
}

Fixed::~Fixed() {
	std::cout << "Destructor called\n";
}

Fixed::Fixed(const Fixed& other) {
	std::cout << "Copy constructor called\n";
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& other) {
	std::cout << "Copy assignment operator called\n";
	if (this != &other){
		this->_raw = other.getRawBits();
	}
	return *this;
}
