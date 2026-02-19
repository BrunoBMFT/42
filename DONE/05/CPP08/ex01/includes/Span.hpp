#ifndef SPAN_HPP
# define SPAN_HPP
# include <iostream>
# include <vector>
# include <algorithm>

class Span
{
	private:
		unsigned int		maxSize;
		std::vector<int>	vect;
	public:
		Span();
		Span(unsigned int n);
		Span(const Span &oth);
		Span &operator=(const Span &oth);
		~Span();

		void addNumber(int num);
		void addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end);
		int shortestSpan();
		int longestSpan();

		class FullContainer : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class NotEnoughNumbers : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

#endif