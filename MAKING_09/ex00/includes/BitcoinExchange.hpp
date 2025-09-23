#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include <map>
# include <fstream>//for file
# include <stdlib.h>//for atof

class BitcoinExchange
{
	private:
		std::map<std::string, double> _db;

		void	processLine(std::string input)
		{
			if (input.length() < 12)//stupid fix
				throw BadInput(input);
			std::string date = input.substr(0, 10);
			double num = atof(input.substr(12).c_str());
			if (num < 0)
				throw NumberNotPositive();
			else if (num > 1000)
				throw NumberTooLarge();
			
			//todo use auto?
			std::map<std::string, double>::iterator pos = _db.lower_bound(date);
			if (pos->first != date && pos != _db.begin())//this should be safe enough, right?
				--pos;
			//*calculate (make func for this)
			double calcValue = pos->second * num;
			std::cout << date << " => " << num << " = " << calcValue << std::endl;
		}

	public:
		BitcoinExchange()
		{
			std::ifstream file("data.csv");
			if (!file.is_open())
				throw FileOpenFail();

			std::string line;
			getline(file, line);//todo skip, dont forget to parse this
			while (getline(file, line))
			{
				std::string::size_type sep = line.find(",");//eww
				std::string date = line.substr(0, sep);
				std::string value = line.substr(sep + 1);//wtf
				_db[date] = atof(value.c_str());//shit
			}
		}

		BitcoinExchange(const BitcoinExchange& oth) {
			*this = oth;
		}

		BitcoinExchange operator=(const BitcoinExchange& oth) {
			//if !=
			_db = oth._db;
			return *this;
		}

		~BitcoinExchange() {}

		void execute(char *av) {
			std::ifstream file(av);
			if (!file.is_open())
				throw std::runtime_error("Error: could not open file.\n");

			std::string input;
			getline(file, input);//todo parse first

			while (getline(file, input)) {
				try {
					processLine(input);
				} catch (std::exception &e) {
					std::cerr << e.what() << std::endl;
				}
			}
		}

		

		//exceptions
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


