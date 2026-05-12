#ifndef RPN_HPP
# define RPN_HPP
# include <iostream>
# include <stack>

enum Token
{
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVISION,
};

class RPN
{
	private:
		std::stack<int> stack;
	public:
		RPN();
		RPN(const RPN& oth);
		RPN operator=(const RPN& oth);
		~RPN();

		bool	isToken(int c);
		bool	validString(char *str);
		int	getToken(int c);
		void execute(char *str);



		class Exception : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

#endif


