#include "../includes/BitcoinExchange.hpp"

//*CONSTRUCTORS
BitcoinExchange::BitcoinExchange()
{
	std::ifstream file("data.csv");
	if (!file.is_open())
		throw FileOpenFail();

	std::string line;
	getline(file, line);

	while (getline(file, line))
	{
		std::string::size_type sep = line.find(",");
		std::string date = line.substr(0, sep);
		std::string value = line.substr(sep + 1);
		_db[date] = atof(value.c_str());
	}
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& oth) {
	*this = oth;
}
BitcoinExchange BitcoinExchange::operator=(const BitcoinExchange& oth)
{
	_db = oth._db;
	return (*this);
}
BitcoinExchange::~BitcoinExchange() {}



//*FUNCTIONS
std::string BitcoinExchange::getDate(std::string input)
{
	size_t sep = input.find(" |");
	std::string temp = input.substr(0, sep);

	if (input.length() < 14)
		throw BadInput(temp);

	if (temp.size() != 10 || temp[4] != '-' || temp[7] != '-')
		throw BadInput(temp);

	int testYear = atoi(temp.substr(0, 4).c_str());
	int testMonth = atoi(temp.substr(5, 2).c_str());
	int testDay = atoi(temp.substr(8, 2).c_str());

	if (testYear < 2009 || testYear > 2022)
		throw BadInput(temp);
		
	if (testMonth < 1 || testMonth > 12)
		throw BadInput(temp);
		
	if (testDay < 1 || testDay > 31)
		throw BadInput(temp);
		
	if (testDay > 30 && (testMonth == 4 || testMonth == 6 || testMonth == 9 || testMonth == 11))
		throw BadInput(temp);
		
	if (testMonth == 2 && testDay > 29)
		throw BadInput(temp);
		
	if (testMonth == 2 && testYear % 4 != 0 && testDay > 28)
		throw BadInput(temp);

	return (temp);
}

void	BitcoinExchange::processLine(std::string input)
{
	std::string date = getDate(input);

	double num = atof(input.substr(12).c_str());
	if (num < 0)
		throw NumberNotPositive();
	else if (num > 1000)
		throw NumberTooLarge();
	
	std::map<std::string, double>::iterator dbIte = _db.lower_bound(date);
	if (dbIte->first != date && dbIte != _db.begin())
		--dbIte;
	double calcValue = dbIte->second * num;
	std::cout << date << " => " << num << " = " << calcValue << std::endl;
}

void	BitcoinExchange::execute(char *input)
{
	std::ifstream file(input);
	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");

	std::string line;
	getline(file, line);

	while (getline(file, line)) {
		try {
			processLine(line);
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}
}



//*EXCEPTIONS
const char *BitcoinExchange::FileOpenFail::what() const throw() {
	return ("Error: could not open file.");
}
BitcoinExchange::BadInput::BadInput(const std::string& input) 
	: _msg("Error: bad input => " + input) {}
BitcoinExchange::BadInput::~BadInput() throw() {}
const char *BitcoinExchange::BadInput::what() const throw() {
	return (_msg.c_str());
}
const char *BitcoinExchange::NumberNotPositive::what() const throw() {
	return ("Error: not a positive number.");
}
const char *BitcoinExchange::NumberTooLarge::what() const throw() {
	return ("Error: too large a number.");
}

