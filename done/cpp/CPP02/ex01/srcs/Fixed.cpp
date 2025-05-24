#include "Fixed.h"
# include <math.h>

void	Fixed::setRawBits(int const raw){
	this->_raw = raw;
}

int		Fixed::getRawBits(void) const{
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

Fixed::Fixed(const int value){
	_raw = value << _frac;
	std::cout << "Int constructor called\n";
}

Fixed::Fixed(const float value){
	_raw = (int)roundf(value * (1 << _frac));
	std::cout << "Float constructor called\n";
}

Fixed& Fixed::operator=(const Fixed& other) {
	std::cout << "Copy assignment operator called\n";
	if (this != &other)
		this->_raw = other.getRawBits();
	return *this;
}

float Fixed::toFloat(void) const{
	return (float)_raw / (float)(1 << _frac);
}

int Fixed::toInt(void) const{
	return (int)(_raw >> _frac);
}

std::ostream&	operator<<(std::ostream &out, Fixed const &fixed) {
	out << fixed.toFloat();
	return out;
}
