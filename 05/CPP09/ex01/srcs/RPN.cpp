#include "../includes/RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& oth) {
	*this = oth;
}

RPN RPN::operator=(const RPN& oth)
{
	if (this != &oth) {
		stack = oth.stack;
	}
	return (*this);
}

RPN::~RPN() {}

bool	RPN::isToken(int c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (true);
	return (false);
}

bool	RPN::validString(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && !isToken(str[i]) && !isdigit(str[i]))
		{
			std::cout << "Error" << std::endl;
			return (false);
		}
		i++;
	}
	return (true);
}

int	RPN::getToken(int c)
{
	if (c == '+')
		return (ADD);
	else if (c == '-')
		return (SUBTRACT);
	else if (c == '*')
		return (MULTIPLY);
	else if (c == '/')
		return (DIVISION);
	return (-1);
}
void RPN::execute(char *str)
{
	int i = 0; 
	while (str[i])
	{
		if (str[i] == ' ') {
			i++;
			continue;
		}
		else if (isdigit(str[i]))
			stack.push(str[i]);
		else
		{
			int n2 = stack.top() - '0';
			stack.pop();
			int n1 = stack.top() - '0';
			stack.pop();
			int token = getToken(str[i]);
			if (token == ADD)
				stack.push((n1 + n2) + '0');
			else if (token == SUBTRACT)
				stack.push((n1 - n2) + '0');
			else if (token == MULTIPLY)
				stack.push((n1 * n2) + '0');
			else if (token == DIVISION) {
				if (n1 == 0 || n2 == 0) {
					std::cout << "0" << std::endl;
					return ;
				}
				stack.push((n1 / n2) + '0');
			}
		}
		i++;
	}
	std::cout << stack.top() - '0' << std::endl;
}



const char *RPN::Exception::what() const throw() {
	return ("");
}

