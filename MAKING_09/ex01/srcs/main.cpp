#include "../includes/RPN.hpp"
#include <stack>
#include <vector>//only to start
#include <iostream>

std::vector<char> createTest() 
{
	std::vector<char> vec;
	vec.push_back('7');
	vec.push_back('7');
	vec.push_back('*');
	vec.push_back('7');
	vec.push_back('-');

	for (std::vector<char>::iterator it = vec.begin();
	it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	return (vec);
}

bool	isValid(int c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (true);
	return (false);
}

void printStack(std::stack<double> stack)
{
	while (!stack.empty()) {
		std::cout << stack.top() << " ";
		stack.pop();
	}
	std::cout << std::endl;
}

int main(void)
{
	std::vector<char> vec = createTest();


	std::stack<double> stack;
	
	for (std::vector<char>::iterator it = vec.begin();
	it != vec.end(); 
	++it)
	{
		if (isdigit(*it))
			stack.push(*it);//so stupid
		else if (isValid((*it)))
		{
			int n1, n2;
			n1 = stack.top();
			stack.pop();
			n2 = stack.top();
			stack.pop();
			//calculate n1 (Token) n2, save it on top
			double final;
			if (*it == '+')
				final = n1 + n2;
			else if (*it == '-')
				final = n1 - n2;
			else if (*it == '*')
				final = n1 * n2;
			else if (*it == '/')
				final = n1 / n2;
			stack.push(final);
		}
		printStack(stack);
	}


	return (0);
}
