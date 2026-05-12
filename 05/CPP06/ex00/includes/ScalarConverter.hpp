#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <iomanip>
# include <stdlib.h>

enum type {
	CHAR = 0,
	INT = 1,
	FLOAT = 2,
	DOUBLE = 3,
	P_INF = 4,
	N_INF = 5,
	NAN = 6,
	INVALID = 7
};

class ScalarConverter {
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		ScalarConverter &operator=(const ScalarConverter &other);
		~ScalarConverter();
		static int		_int;
		static float	_float;
		static double	_double;
	public:

		static void	convert(std::string const str);

};

type	getType(std::string const str);
bool	isChar(std::string const str);
bool	isInt(std::string const str);
int		isFloat(std::string const str);
void	printSpecials(int type);
void	printChar(int c);
void	printInt(int i);
void	printFloat(float f);
void	printDouble(double d);
#endif
