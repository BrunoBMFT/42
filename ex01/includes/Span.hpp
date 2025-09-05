#ifndef SPAN_HPP
# define SPAN_HPP
# include <iostream>
# include <vector>

class Span
{
	private:
		unsigned int		max;
		std::vector<int>	vect;
	public:
		Span();
		Span(unsigned int n);

		//COPIES!!!

		~Span();

		
		void addNumber(int num);
		int biggestSpan();
		int shortestSpan();

	// // Exceptions 
	// // !RENAME
	// class FullContainerException : public std::exception
	// {
	// 	public:
	// 		virtual const char *what() const throw();
	// };

	// class NotEnoughNumbersException : public std::exception
	// {
	// 	public:
	// 		virtual const char *what() const throw() {}
	// };
};

#endif