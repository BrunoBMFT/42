#ifndef RPN_HPP
# define RPN_HPP
# include <iostream>
//include a type of container
//stack
class RPN
{
	private:

	public:
		//*CONSTRUCTORS
		RPN();
		RPN(const RPN& oth);
		RPN operator=(const RPN& oth);
		~RPN();

		//*FUNCTIONS

		//*EXCEPTIONS
		class Exception : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

#endif


