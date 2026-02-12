#include "PmergeMe.hpp"
#include <unistd.h>
void tester();

void tester()
{
    
    std::cout <<BLUE<< "\n\t\tTester CPP 09: ex 2:\n"<< END << std::endl;
    std::cout << "this tester will create 10 random sequences and organize" << std::endl;
    std::cout << "it with the algorithm of ford jonson:\n" << std::endl;
    
    for (int i = 0; i < 100; i++)
    {
        std::cout << ORANGE << "Case " << i + 1 << ":" << END  << std::endl;
        PmergeMe(1, NULL);
        sleep(2);
    }   
}

int main(int ac, char **av)
{
    if (TEST)
    {
        std::srand(time(NULL));
        tester();
        return (0);
    }
    if (ac < 2)
        return(std::cerr << "Error: no args!" << std::endl, 1);
    try
    {
        PmergeMe a(ac--,&av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

