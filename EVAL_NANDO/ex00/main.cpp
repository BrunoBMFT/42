#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Invalid number of files!" << std::endl;
        return 1;
    }
    try
    {
        BitcoinExchange btc;
        btc.analise_doc(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
