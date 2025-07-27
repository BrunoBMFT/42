
#include "../includes/Array.hpp"

int main(void)
{
    srand(time(NULL));;

    std::cout << "INT TESTS:" << std::endl;
    Array<int> empty();
    Array<int> test(5);

    for (int i = 0; i < 5; i++)
        std::cout << test[i] << " ";
    std::cout << std::endl;


    return 0;
}
