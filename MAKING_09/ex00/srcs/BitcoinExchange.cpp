#include "BitcoinExchange.hpp"


//exception
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

