#include "../includes/BitcoinExchange.hpp"
#include <fstream>
#include <map>
#include <stdlib.h>//for atof

//todo make these modular
std::map<std::string, double> saveDb()
{
	std::ifstream file("data.csv");//use .is_open() to check
	if (!file.is_open())
		throw std::runtime_error("file failed to open\n");
	std::map<std::string, double> db;

	std::string line;
	getline(file, line);//skip, dont forget to parse this
	while (getline(file, line))
	{
		std::string::size_type sep = line.find(",");//eww
		std::string date = line.substr(0, sep);
		std::string value = line.substr(sep + 1);//wtf
		db[date] = atof(value.c_str());//shit
	}

	//*testing
	// for (std::map<std::string, double>::iterator it = db.begin(); it != db.end(); ++it)
	// 	std::cout << "date: " << it->first << " value: " << it->second << std::endl;

	return (db);//this wont have to return a map, it will be in class
}

//technically this doesnt need to be a map
// i need to save it somehow without using more containers
// i could do it line by line using getline to be simpler, since i dont exactly need it saved


// i have the db, i could justse getline, compare dates, calculate value, print it

//TODO MAP HAS LOWER_BOUND() TO FIND THE CLOSEST DATE!!!


void	processData(std::map<std::string, double> db, char **av)
{
	std::ifstream file(av[1]);
	if (!file.is_open())//THIS ISNT CHECKING ANYTHING
		throw std::runtime_error("file failed to open\n");

	
	std::string line;
	getline(file, line);//*parse


	while (getline(file, line))//parse input
	{
		// std::cout << "input: " << line << std::endl;
		std::string date = line.substr(0, 10);
		std::cout << "date: " << date << std::endl;
		//! LOWERBOUND ISNT WORKING CORRECTLY
		std::map<std::string, double>::iterator pos = db.lower_bound(date);//!doesnt work how i wanted it
		std::cout << "data in db: " << pos->first << std::endl;
		//TODO now calculate the value difference and print it
	}


}


int main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "Invalid number of arguments" << std::endl;
		return 1;
	}
	//*save db
	std::map<std::string, double> db;
	try { //stupid shit
		db = saveDb();
		
		processData(db, av);
	} catch (std::exception &e) {
		std::cerr << e.what();
		return 1;
	}




	// BitcoinExchange exchange;
	// exchange.execute(argv[1]);
	return 0;
}
