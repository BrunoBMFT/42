#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include <map>
# include <fstream>
# include <stdlib.h>

class BitcoinExchange
{
	private:
		std::map<std::string, double> _db;

		void		processLine(std::string input);
		std::string	getDate(std::string input);

	public:
		//*CONSTRUCTORS
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& oth);
		BitcoinExchange operator=(const BitcoinExchange& oth);
		~BitcoinExchange();

		//*FUNCTIONS
		void execute(char *input); 

		//*EXCEPTIONS
		class FileOpenFail : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class BadInput : public std::exception
		{
			private:
				std::string _msg;
			public:
				BadInput(const std::string& input);
				virtual const char *what() const throw();
				~BadInput() throw();
		};
		class NumberNotPositive : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class NumberTooLarge : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

#endif


