
#include "../includes/Array.hpp"

template <typename var>
void	printArray(Array<var> arr) {
	for (unsigned int i = 0; i < arr.size(); i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

int main(void)
{
	srand(time(NULL));;
	
	Array<long> empty;
	Array<long> test1(5);
	for (unsigned int i = 0; i < test1.size(); i++)
		test1[i] = rand() % 100;
		// test1[i] = i + 'a';//for chars
	Array<long> test2(test1);
	Array<long> test3 = test1;

	std::cout << "CREATION:" << std::endl;
	std::cout << "==========================" << std::endl;
	std::cout << "default:" << std::endl;
	printArray(empty);
	std::cout << "==========================" << std::endl;
	std::cout << "number:" << std::endl;
	printArray(test1);
	std::cout << "==========================" << std::endl;
	std::cout << "copy:" << std::endl;
	printArray(test2);
	std::cout << "==========================" << std::endl;
	std::cout << "assignment:" << std::endl;
	printArray(test3);
	std::cout << std::endl;

	

	std::cout << "MODIFICATION:" << std::endl;
	std::cout << "==========================" << std::endl;
	std::cout << "number before:" << std::endl;
	printArray(test1);
	test1[4] = 126;
	std::cout << "after:" << std::endl;
	printArray(test1);
	std::cout << "==========================" << std::endl;
	std::cout << "copy before:" << std::endl;
	printArray(test2);
	test2[4] = 125;
	std::cout << "after:" << std::endl;
	printArray(test2);
	std::cout << "==========================" << std::endl;
	std::cout << "assignment before:" << std::endl;
	printArray(test3);
	test3[4] = 124;
	std::cout << "after:" << std::endl;
	printArray(test3);
	std::cout << std::endl;



	std::cout << "OUT OF BOUNDS:" << std::endl;
	{
		std::cout << "==========================" << std::endl;
		std::cout << "trying to read element out of bounds:" << std::endl;
		try {
			std::cout << test3[100] << std::endl;
		} catch (std::exception &e) {
			std::cout << "exception caught: " << e.what() << std::endl;
		}
		std::cout << "trying to write element out of bounds:" << std::endl;
		try {
			test3[100] = 100;
		} catch (std::exception &e) {
			std::cout << "exception caught: " << e.what() << std::endl;
		}
	}

	
	
	


    return 0;
}
