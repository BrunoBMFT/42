#include <Fixed.h>
#include <iostream>

int main( void ) {
	/*{
	Fixed a;
	Fixed ret;
	Fixed const b(10);
	Fixed const c(42.42f);
	Fixed const d( b );
	a = Fixed( 1234.4321f );
	if (b < c)
		std::cout << "b < c | b: " << b << " c: " << c << std::endl;
	else if (b > c)
		std::cout << "b > c | b: " << b << " c: " << c << std::endl;
	if (b <= d)
		std::cout << "b <= d | b: " << b << " d: " << d << std::endl;
	else if (b >= d)
		std::cout << "b >= d | b: " << b << " d: " << d << std::endl;
	if (b == c)
		std::cout << "b == c | b: " << b << " c: " << c << std::endl;
	else if (b != c)
		std::cout << "b != c | b: " << b << " c: " << c << std::endl;
	ret = b + c;
	std::cout << "b + c = " << ret << std::endl;
	ret = b - c;
	std::cout << "b - c = " << ret << std::endl;
	ret = b * c;
	std::cout << "b * c = " << ret << std::endl;
	ret = b / c;
	std::cout << "b / c = " << ret << std::endl;
	}*/
	{
		Fixed a;
		Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

		std::cout << a << std::endl;
		std::cout << ++a << std::endl;
		std::cout << a << std::endl;
		std::cout << a++ << std::endl;
		std::cout << a << std::endl;

		std::cout << b << std::endl;

		std::cout << Fixed::max( a, b ) << std::endl;
	}
	return 0;
}