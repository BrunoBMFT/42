#include "../includes/BitcoinExchange.hpp"
#include <fstream>
#include <vector>
#include <stdlib.h>//for atof
//figure out input.txt date|value line

std::vector<std::string> saveFile(std::string infile)
{
	std::vector<std::string> vec;
	std::ifstream file(infile.c_str());//in relation to compilation
	if (!file)
		throw std::runtime_error("file failed to open\n");
	std::string line;
	while (std::getline(file, line))
		vec.push_back(line);
	// for (size_t i = 0; i < vec.size(); i++)//testing
	// 	std::cout << vec[i] << std::endl;
	return (vec);
}

void	processDate(std::string input, std::vector<std::string> db)
{	
	// std::cout << "input: " << input << std::endl;
	std::string date = input.substr(0, 10);//does this allocate
	//todo parse the date

	std::string temp;
	for (size_t i = 0; i < db.size(); i++) {
		if (date > db[i].substr(0, 10))
			temp = db[i];//why does it not work with break???
	}
	// std::cout << "in db: "<< temp << std::endl;

	//*calculate info
	//! USE FIND INSTEAD OF EVERYTHING ELSE
	float inputNum = static_cast<float>(atof(input.substr(12, input.length()).c_str()));
	float dbNum = static_cast<float>(atof(temp.substr(11, temp.length()).c_str()));

	// std::cout << "inputNum: "<< inputNum << std::endl;
	float final = inputNum * dbNum;
	//*print info
	std::cout << input << " = " << final << std::endl;
}

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "Invalid number of arguments" << std::endl;
		return 1;
	}
	
	//*save db
	std::vector<std::string> db;
	try { //stupid shit
		db = saveFile("data.csv");
	} catch (std::exception &e) {
		std::cerr << e.what();
		return 1;
	}

	//*save input
	std::vector<std::string> input;
	try {//more stupid shit
		input = saveFile(av[1]);
	} catch (std::exception &e) {
		std::cerr << e.what();
		return 1;
	}

	// processDate(input[1], db);
	//*loop through input
	for (size_t i = 0; i < input.size(); i++)
		processDate(input[i], db);
	return 0;
}
