#ifndef RPN_HPP
# define RPN_HPP
# include <iostream>
# include <stack>

bool	isToken(int c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (true);
	return (false);
}

bool	validString(char *str)// todo THROW
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

enum Token
{
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVISION,
};

int	getToken(int c)
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

void	printStack(std::stack<int> stack)
{
	while (!stack.empty())
	{
		std::cout << stack.top() - '0' << " ";
		stack.pop();
	}
	std::cout << std::endl;
}

class RPN
{
	private:
		std::stack<int> stack;
	public:
		//*CONSTRUCTORS
		RPN();
		RPN(const RPN& oth);
		RPN operator=(const RPN& oth);
		~RPN();

		//*FUNCTIONS
		void execute(char *str)
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
					//rename vars
					int n2 = stack.top() - '0';//UGLY
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
					else if (token == DIVISION)
						stack.push((n1 / n2) + '0');
				}
				printStack(stack);//inverse
				i++;
			}
			std::cout << stack.top() - '0' << std::endl;
		}

















		//*EXCEPTIONS
		class Exception : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

#endif


