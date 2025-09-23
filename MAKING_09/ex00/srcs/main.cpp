#include "../includes/BitcoinExchange.hpp"
//todo create exceptions for everything

/*
	while (input line)
	{
		try
		{
			parse date
			process data
			print data
		}
		catch
		{
			whatever
		}
	}

*/

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "Error: could not open file." << std::endl;//change
		return 1;
	}

	try {
		BitcoinExchange btc;
		btc.execute(av[1]);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
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
