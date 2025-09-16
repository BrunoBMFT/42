#include "../includes/easyfind.hpp"
# include <vector>
# include <list>
# include <deque>

template <typename Container>
void create_container(Container& cntr, int size, int tofind){
	typename Container::iterator it;

	for (int i = 0; i < size; i++)
		cntr.push_back(i);
	std::cout << "find: [" << tofind << "] in container: { ";
	for (it = cntr.begin(); it != cntr.end(); ++it)
		std::cout << *it << " ";
	std::cout << "}" << std::endl;
}

template <typename Container>
void find_test(Container cntr, int tofind) {
	try {
		typename Container::const_iterator r = easyfind(cntr, tofind);
		std::cout << "found: " << *r << " in the container" << std::endl;
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

void vector_test(int size, int tofind){
	std::vector<int> vec;
	create_container(vec, size, tofind);
	find_test(vec, tofind);
}

void list_test(int size, int tofind){
	std::list<int> lst;
	create_container(lst, size, tofind);
	find_test(lst, tofind);
}

void deque_test(int size, int tofind){
	std::deque<int> queue;
	create_container(queue, size, tofind);
	find_test(queue, tofind);
}

int	main(void){
	std::cout << "===========================" << std::endl;
	std::cout << "VECTOR TESTS:" << std::endl;
	vector_test(6, 2);
	vector_test(4, 100);
	std::cout << "===========================" << std::endl;
	std::cout << "LIST TESTS:" << std::endl;
	list_test(6, 2);
	list_test(4, 100);
	std::cout << "===========================" << std::endl;
	std::cout << "DEQUE TESTS:" << std::endl;
	deque_test(6, 2);
	deque_test(4, 100);
}