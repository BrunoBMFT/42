#include "Fixed.h"
#include <math.h>

void 	Fixed::setRawBits(int const raw){
	this->_raw = raw;
}

int 	Fixed::getRawBits(void) const{
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
	setRawBits(value << _frac);
	std::cout << "Int constructor called\n";
}

Fixed::Fixed(const float value){
	setRawBits((int)roundf(value * (1 << _frac)));
	std::cout << "Float constructor called \n";
}

Fixed& Fixed::operator=(const Fixed& other) {
	std::cout << "Copy assignment operator called\n";
	if (this != &other){
		setRawBits(other.getRawBits());
	}
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


bool	Fixed::operator>(Fixed const &other) const{
	return getRawBits() > other.getRawBits();
}
bool	Fixed::operator<(Fixed const &other) const{
	return getRawBits() < other.getRawBits();
}
bool	Fixed::operator>=(Fixed const &other) const{
	return getRawBits() >= other.getRawBits();
}
bool	Fixed::operator<=(Fixed const &other) const{
	return getRawBits() <= other.getRawBits();
}
bool	Fixed::operator==(Fixed const &other) const{
	return getRawBits() == other.getRawBits();
}
bool	Fixed::operator!=(Fixed const &other) const{
	return getRawBits() != other.getRawBits();
}


Fixed&	Fixed::operator++(){
	_raw++;
	return (*this);
}
Fixed	Fixed::operator++(int){
	Fixed temp(*this);
	operator++();
	return (temp);
}
Fixed&	Fixed::operator--(){
	_raw--;
	return (*this);
}
Fixed	Fixed::operator--(int){
	Fixed temp(*this);
	operator--();
	return (temp);
}


Fixed	Fixed::operator+(Fixed const &other) const{
	Fixed ret;
	ret.setRawBits(getRawBits() + other.getRawBits());
	return (ret);
}
Fixed	Fixed::operator-(Fixed const &other) const{
	Fixed ret;
	ret.setRawBits(getRawBits() - other.getRawBits());
	return (ret);
}
Fixed	Fixed::operator*(Fixed const &other) const{
	Fixed ret;
	ret.setRawBits(getRawBits() * other.getRawBits() >> _frac);
	return (ret);
}
Fixed	Fixed::operator/(Fixed const &other) const{
	Fixed ret;
	ret.setRawBits(getRawBits() / other.getRawBits() << _frac);
	return (ret);
}


Fixed&	Fixed::min(Fixed &f1, Fixed &f2){
	if (f1 < f2)
		return (f1);
	return (f2);
}
Fixed	Fixed::min(Fixed const &f1, Fixed const &f2){
	if (f1 < f2)
		return (f1);
	return (f2);
}
Fixed&	Fixed::max(Fixed &f1, Fixed &f2){
	if (f1 > f2)
		return (f1);
	return (f2);
}
Fixed	Fixed::max(Fixed const &f1, Fixed const &f2){
	if (f1 > f2)
		return (f1);
	return (f2);
}