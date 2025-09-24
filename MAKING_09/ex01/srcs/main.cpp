#include "../includes/RPN.hpp"
#include <iostream>
#include <stack>

/*
	9 8 * 7 -
	adds 9 to stack									9
	adds 8 to stack									9 8
	finds *											9 8 * (found, not saved)
	saves 9 and 8									* (removes 9 and 8)
	multiplies them to make 72						(removes *, calculate 72)
	saves 72 onto the beginning of the list			72
	adds 7 to stack									72 7
	finds -											72 7 - (found, not saved)
	saves 72 and 7									- (removes 72 and 7)
	substracts 7 from 72							(removes -, calculate 65)
	saves 65 onto stack								65
*/

bool	isToken(int c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (true);
	return (false);
}

bool	validString(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && !isToken(str[i]) && !isdigit(str[i]))
		{
			std::cout << "Error\n";
			return (false);
		}
		i++;
	}
	return (true);
}

void	printStack(std::stack<char> stack)
{
	while (!stack.empty())
	{
		std::cout << stack.top() << " ";
		stack.pop();
	}
	std::cout << std::endl;
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
	if (!validString(av[1]))
		return 1;

	std::stack<char> stack;
	char *str = av[1];
	int i = 0; 
	while (str[i])
	{
		if (str[i] == ' ') {
			i++;
			continue;
		}
		stack.push(str[i]);
		//push to stack if number
		//save 2 numbers and do operation if token

		i++;
	}
	printStack(stack);//prints in reverse
	return (0);
}
