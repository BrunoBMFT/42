#include "../includes/ScalarConverter.hpp"

ScalarConverter::ScalarConverter(){}
ScalarConverter::ScalarConverter(const ScalarConverter &other){*this = other;}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other){if (this != &other)*this = other;return *this;}
ScalarConverter::~ScalarConverter() {}

int ScalarConverter::_int = 0;
float ScalarConverter::_float = 0.0f;
double ScalarConverter::_double = 0.0;

void	printSpecials(int type) {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	if (type == P_INF){
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
	}
	else if (type == N_INF){
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
	else if (type == NAN){
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
}
void	printChar(int c) {
	if (c < 0 || c > 127)
		std::cout << "char: impossible" << std::endl;
	else if (c < 32 || c == 127)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: \'" << static_cast<char>(c) << "\'" << std::endl;
}
void	printInt(int i) {
	std::cout << "int: " << i << std::endl;
}
void	printFloat(float f) {
	std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
}
void	printDouble(double d) {
	std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}

bool	isChar(std::string const str) {
	if (!isdigit(str[0]))
		return (true);
	return (false);
}

bool	isInt(std::string const str) {
	size_t i = 0;

	if (str[0] == '-' || str[0] == '+')
		i++;
	if (i == str.length())
		return false;
	while (str[i]){
		if (!isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	isFloat(std::string const str) {
	int sign = 0;
	if (str[0] == '-' || str[0] == '+')
		sign++;
	size_t i = sign;
	bool	hasDigBefore = false;
	bool	hasDigAfter = false;
	while (str[i] && isdigit(str[i])){
		hasDigBefore = true;
		i++;
	}
	if (!str[i] || str[i] != '.')
		return (0);
	i++;
	while (str[i] && isdigit(str[i])){
		hasDigAfter = true;
		i++;
	}
	if (!hasDigBefore || !hasDigAfter)
		return (0);
	if (str[i] && i == str.length() - 1 && str[i] == 'f')
		return (FLOAT);
	if (i == str.length())
		return (DOUBLE);
	return (0);
}

type	getType(std::string const str) {
	if (!str.compare("nan") || !str.compare("nanf"))
		return (NAN);
	if (!str.compare("+inf") || !str.compare("+inff"))
		return (P_INF);
	if (!str.compare("-inf") || !str.compare("-inff"))
		return (N_INF);
	if (isChar(str))
		return (CHAR);
	if (isInt(str))
		return (INT);
	int temp = isFloat(str);
	if (temp == FLOAT)
		return (FLOAT);
	else if (temp == DOUBLE)
		return (DOUBLE);
	return (INVALID);
}

void	ScalarConverter::convert(std::string const str) {
	type t = getType(str);
	switch (t) {
		case P_INF:
			printSpecials(P_INF);
			return ;
		case N_INF:
			printSpecials(N_INF);
			return ;
		case NAN:
			printSpecials(NAN);
			return ;
		case CHAR:
			_int = static_cast<int>(str[0]);
			_float = static_cast<float>(_int);
			_double = static_cast<double>(_int);
			break;
		case INT:
			_int = atoi(str.c_str());
			_float = static_cast<float>(_int);
			_double = static_cast<double>(_int);
			break;
		case FLOAT:
			_float = atof(str.c_str());
			_int = static_cast<int>(_float);
			_double = static_cast<double>(_float);
			break;
		case DOUBLE:
			_double = static_cast<double>(atof(str.c_str()));
			_int = static_cast<int>(_double);
			_float = static_cast<float>(_double);
			break;
		case INVALID:
			std::cout << "INVALID\n";
			return ;
	}
	printChar(_int);
	printInt(_int);
	printFloat(_float);
	printDouble(_double);
}
