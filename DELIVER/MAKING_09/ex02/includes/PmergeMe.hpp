#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <vector>
# include <deque>
# include <cstdlib>//atoi

class PmergeMe
{
	private:
	public:
		std::vector<unsigned int> _vector;//priv
		int _size;//priv
		double _vectorTime;
		double _dequeTime;
		//*CONSTRUCTORS
		PmergeMe();
		PmergeMe(char **args);
		PmergeMe(const PmergeMe& oth);//not done
		PmergeMe operator=(const PmergeMe& oth);//not done
		~PmergeMe();//not done

		//*FUNCTIONS
		void	printBefore();
		void	printAfter();
		void	printTimeVector();
		void	printTimeDeque();

		void	execute();

		//*EXCEPTIONS
		class Exception : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

#endif


