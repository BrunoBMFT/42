#include "../includes/BitcoinExchange.hpp"
#include <fstream>
#include <map>
#include <stdlib.h>//for atof
//todo create exceptions for everything
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!

std::map<std::string, double> saveDb()
{
	std::ifstream file("data.csv");
	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.\n");
	std::map<std::string, double> db;

	std::string line;
	getline(file, line);//todo skip, dont forget to parse this
	while (getline(file, line))
	{
		std::string::size_type sep = line.find(",");//eww
		std::string date = line.substr(0, sep);
		std::string value = line.substr(sep + 1);//wtf
		db[date] = atof(value.c_str());//shit
	}

	return (db);//todo this wont have to return a map, it will be in class
}
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!

bool	processLine(std::map<std::string, double> db, std::string input)
{
	if (input.length() < 12){//stupid fix
		std::cout << "Error: bad input => " << input << std::endl;
		return (false);
	}
	std::string date = input.substr(0, 10);
	double num = atof(input.substr(12).c_str());
	if (num < 0) {
		std::cout << "Error: not a positive number." << std::endl;
		return (false);
	}
	else if (num > 1000){
		std::cout << "Error: too large a number." << std::endl;
		return (false);
	}
	//todo use auto?
	//todo parse dates using strptime
	std::map<std::string, double>::iterator pos = db.lower_bound(date);
	if (pos->first != date && pos != db.begin())//this should be safe enough, right?
		--pos;
	
	//*calculate (make func for this)
	double calcValue = pos->second * num;
	std::cout << date << " => " << num << " = " << calcValue << std::endl;
	return (true);
}
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!

void	processData(std::map<std::string, double> db, char **av)
{
	std::ifstream file(av[1]);
	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.\n");

	std::string input;
	getline(file, input);//todo parse first

	while (getline(file, input))
		if (!processLine(db, input))
			continue ;
}
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
//!NOW PUT IT IN CLASSES!!!
int main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}

	try {
		BitcoinExchange btc;
		btc.process(av[1]);
	} catch (std::exception &e) {
		std::cerr << e.what();
		return 1;
	}

	// std::map<std::string, double> db;
	// try { //stupid shit
	// 	db = saveDb();

	// 	processData(db, av);
	// } catch (std::exception &e) {
	// 	std::cerr << e.what();
	// 	return 1;
	// }

	return 0;
}
